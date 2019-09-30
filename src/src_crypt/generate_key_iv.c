/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_key_iv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 11:38:26 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 12:00:22 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"
#include "ft_ssl_hash.h"

static char	*get_salt(void)
{
	int		fd;
	char	*salt;

	fd = open("/dev/urandom", O_RDONLY);
	if (!(salt = malloc(9)))
		return (NULL);
	salt[8] = '\0';
	if (read(fd, salt, 8) == -1)
	{
		free(salt);
		return (NULL);
	}
	return (salt);
}

static int	check_salt(t_des_flags *f)
{
	char	*tmp;
	int		len;

	if (f->salt)
	{
		if ((len = ft_strlen(f->salt)) > 16 || !hex_expr(f->salt))
		{
			ft_putstr_fd("Problem with salt expression!", 2);
			return (0);
		}
		if (len < 16)
		{
			if (!(tmp = ft_strnew(17)))
				return (0);
			ft_strcpy(tmp, f->salt);
			while (len < 16)
				tmp[len++] = '0';
			free(f->salt);
			f->salt = tmp;
		}
		f->salt = hex2dec(f->salt, 8);
	}
	else if (!(f->salt = get_salt()))
		return (0);
	return (1);
}

static int	pbkdf2(t_des_flags *f)
{
	char			*res;
	t_md5_context	c;

	if (!(res = ft_strjoin(f->passwd, f->salt)))
		return (0);
	c = treat_md5(res, ft_strlen(f->passwd) + 8);
	free(res);
	res = str_msg_md5(c);
	if (!(f->key = (char*)malloc(17)))
		return (0);
	if (!(f->iv = (char*)malloc(17)))
	{
		free(f->key);
		return (0);
	}
	ft_memcpy(f->key, res, 16);
	ft_memcpy(f->iv, res + 16, 16);
	f->key[16] = '\0';
	f->iv[16] = '\0';
	free(res);
	if (!f->key || !f->iv)
		return (0);
	return (1);
}

int			ft_generate_iv_keys(t_des_flags *f, char **str, int *len)
{
	if (f->key)
		return (1);
	if (f->decrypt)
	{
		if (ft_strncmp(*str, "Salted__", 8) || ft_strlen(*str + 8) < 8)
		{
			ft_putstr_fd("ERROR CIPHER\n", 2);
			return (0);
		}
		if (!(f->salt = malloc(9)))
			return (0);
		f->salt[8] = '\0';
		ft_strncpy(f->salt, *str + 8, 8);
		*str += 16;
		*len = ft_strlen(*str);
	}
	if (!f->decrypt && !check_salt(f))
		return (0);
	if (!f->decrypt)
		f->tmp = ft_strjoin("Salted__", f->salt);
	return (pbkdf2(f));
}

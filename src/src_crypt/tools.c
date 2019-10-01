/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:22:21 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 14:23:47 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

int			pretreat_des(t_des_flags *flags, char **str, int *len)
{
	if (flags->in && (flags->fd_in = open(flags->in, O_RDONLY)) == -1)
	{
		file_error("des", flags->in);
		return (0);
	}
	if (flags->out && (flags->fd_out = \
				open(flags->out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		file_error("des", flags->out);
		return (0);
	}
	*len = read_function(flags->fd_in, str);
	*len = (!flags->decrypt && *len % 8 == 0) ? *len + 8 : *len;
	return (1);
}

void		encrypt_base64(t_des_flags *flags, char *str, int len)
{
	char	*out;
	t_u64	outlen;
	int		i;
	char	*key;
	char	*cipher;

	i = 0;
	while (i < len)
	{
		key = ft_strdup(flags->key);
		if (!(cipher = encrypt_des(str + i, key, flags)))
			return ;
		flags->tmp = ft_strjoin(flags->tmp, bin2dec(cipher));
		i += 8;
	}
	if (!(base64_encode(flags->tmp, ft_strlen(flags->tmp), &out, &outlen)))
		return ;
	write(1, out, outlen);
}

static void	print_result(char *text, int fd)
{
	int i;

	i = -1;
	while (++i < 8)
		ft_putchar_fd(text[i], fd);
	free(text);
}

void		crypt_des(t_des_flags *flags, char *str, int len)
{
	int		i;
	char	*text;
	char	*key;

	i = 0;
	while (i < len)
	{
		key = ft_strdup(flags->key);
		if (!flags->decrypt)
		{
			if (!(text = encrypt_des(str + i, key, flags)))
				return ;
		}
		else
		{
			if (!(text = decrypt_des(str + i, key, flags)))
				return ;
		}
		print_result(bin2dec(text), flags->fd_out);
		i += 8;
	}
}

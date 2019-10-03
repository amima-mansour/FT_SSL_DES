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
		cipher = bin2dec(cipher);
		out = ft_strnjoin(flags->tmp, cipher, i, 8);
		free(cipher);
		free(flags->tmp);
		flags->tmp = out;
		i += 8;
	}
	if (!(base64_encode(flags->tmp, i, &out, &outlen)))
		return ;
	print_base64(out, outlen, flags->fd_out);
	free(out);
}

static void	print_result(char *text, int fd, char decrypt)
{
	int		i;
	int		len;
	char	c;

	len = 8;
	if (decrypt && (c = text[7]) <= 8)
	{
		i = 7;
		while (--i >= 0 && text[i] == c)
			;
		if (i == -1)
			i = 0;
		if ((7 - i) == c)
			len = i + 1;
	}
	i = -1;
	while (++i < len)
		ft_putchar_fd(text[i], fd);
	free(text);
}

void		crypt_des(t_des_flags *flags, char *str, int len)
{
	int		i;
	char	*text;
	char	*key;
	int		j;

	i = 0;
	while (i < len)
	{
		key = ft_strdup(flags->key);
		j = -1;
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
		text = bin2dec(text);
		print_result(text, flags->fd_out, flags->decrypt);
		i += 8;
	}
}

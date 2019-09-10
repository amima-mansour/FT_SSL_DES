/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:36:20 by amansour          #+#    #+#             */
/*   Updated: 2019/09/02 09:31:46 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static	t_u64	ft_trim(char *str)
{
	t_u64	start;
	t_u64	end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] != ' ' && str[end] != '\n' && str[end] != '\t' \
				&& str[end] != '\r')
		{
			str[start] = str[end];
			start++;
		}
		end++;
	}
	return (start);
}

static int		base_convert(char *c, char *e, char *s)
{
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < 4)
		if (e[i] == '=')
		{
			ret++;
			c[i] = 0;
		}
	s[0] = (c[0] << 2) | (c[1] >> 4);
	s[1] = (c[1] << 4) | (c[2] >> 2);
	s[2] = (c[2] << 6) | c[3];
	return (ret);
}

static int		treat_base_decode(char *str, char *enc)
{
	int		i;
	int		j;
	char	c[4];

	i = -1;
	while (++i < 4)
	{
		if (!(ft_isalpha(enc[i]) || ft_isdigit(enc[i]) || enc[i] == '+' ||
					enc[i] == '/' || enc[i] == '='))
			return (-1);
	}
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 4)
			if (enc[j] == BASE64[i])
				c[j] = i;
	}
	return (base_convert(c, enc, str));
}

void			base64_decode(char *in, t_u64 len, int fd)
{
	char	*out;
	t_u64	i;
	int		ret;
	t_u64	outlen;

	len = ft_trim(in);
	outlen = (len / 4) * 3;
	if (!(out = malloc(outlen)))
		return ;
	i = 0;
	while (i < outlen)
	{
		if ((ret = treat_base_decode(&(out[i]), in)) == -1)
		{
			errors("Invalid character in input stream.");
			free(out);
			return ;
		}
		i += 3;
		in += 4;
	}
	outlen -= ret;
	write(fd, out, outlen);
	free(out);
}

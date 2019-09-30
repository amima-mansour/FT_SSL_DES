/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:44:45 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 15:47:58 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static	t_u64	encode_base64_size(t_u64 inlen)
{
	t_u64	ret;

	ret = inlen;
	if (inlen % 3 != 0)
		ret += 3 - (inlen % 3);
	ret /= 3;
	ret *= 4;
	return (ret);
}

static	void	treat_base_encode(char **out, char *in, t_u64 len)
{
	t_u64	i;
	t_u64	j;
	t_u32	v;

	i = 0;
	j = 0;
	while (i < len)
	{
		v = (unsigned char)in[i];
		v = i + 1 < len ? v << 8 | (unsigned char)in[i + 1] : v << 8;
		v = i + 2 < len ? v << 8 | (unsigned char)in[i + 2] : v << 8;
		(*out)[j] = BASE64[(v >> 18) & 63];
		(*out)[j + 1] = BASE64[(v >> 12) & 63];
		if (i + 1 < len)
			(*out)[j + 2] = BASE64[(v >> 6) & 63];
		else
			(*out)[j + 2] = '=';
		if (i + 2 < len)
			(*out)[j + 3] = BASE64[v & 63];
		else
			(*out)[j + 3] = '=';
		i += 3;
		j += 4;
	}
}

int				base64_encode(char *in, t_u64 len, char **out, t_u64 *outlen)
{
	if (in == NULL || len == 0)
		return (0);
	*outlen = encode_base64_size(len);
	if (!(*out = malloc(*outlen + 1)))
		return (0);
	(*out)[*outlen] = '\0';
	treat_base_encode(out, in, len);
	return (1);
}

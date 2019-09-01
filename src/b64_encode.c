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

#include "ft_ssl.h"
#include "../libft/libft.h"

static	const	char	g_b64[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'};

static	t_u64			encode_base64_size(t_u64 inlen)
{
	t_u64	ret;

	ret = inlen;
	if (inlen % 3 != 0)
		ret += 3 - (inlen % 3);
	ret /= 3;
	ret *= 4;
	return (ret);
}

static	void			treat_base_encode(char **out, char *in, t_u64 len)
{
	t_u64	i;
	t_u64	j;
	t_u64	v;

	i = 0;
	j = 0;
	while (i < len)
	{
		v = in[i];
		v = i + 1 < len ? v << 8 | in[i + 1] : v << 8;
		v = i + 2 < len ? v << 8 | in[i + 2] : v << 8;
		(*out)[j] = g_b64[(v >> 18) & 0x3F];
		(*out)[j + 1] = g_b64[(v >> 12) & 0x3F];
		if (i + 1 < len)
			(*out)[j + 2] = g_b64[(v >> 6) & 0x3F];
		else
			(*out)[j + 2] = '=';
		if (i + 2 < len)
			(*out)[j + 3] = g_b64[v & 0x3F];
		else
			(*out)[j + 3] = '=';
		i += 3;
		j += 4;
	}
}

char					*base64_encode(char *in, t_u64 len)
{
	char	*out;
	t_u64	elen;

	if (in == NULL || len == 0)
		return (NULL);
	elen = encode_base64_size(len);
	if (!(out = malloc(elen + 1)))
		return (NULL);
	out[elen] = '\0';
	treat_base_encode(&out, in, len);
	return (out);
}

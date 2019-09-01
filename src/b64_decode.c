/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:36:20 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 16:43:05 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

static	const	int		g_b64invs[] = {
	62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };

static	int				b64_isvalidchar(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '+' || c == '/' || c == '=')
		return (1);
	if (c == '\n' || c == ' ' || c == '\r' || c == '\t')
		return (1);
	printf("c = %c\n", c);
	return (0);
}

static	t_u64			size_base64_decode(char *src, t_u64 slen)
{
	t_u64 i;
	t_u64 n;
	t_u64 j;

	j = 0;
	n = 0;
	i = 0;
	printf("SLEN = %llu\n", slen);
	while (i < slen)
	{
		i -= 1;
		while (i < slen && src[i] == ' ')
			++i;
		if (i == slen)
			break ;
		if (((slen - i) >= 2 && src[i] == '\r' && src[i + 1] == '\n') \
		|| src[i] == '\n' || src[i] == '\t' || src[i] == '\r' || src[i] == ' ')
			continue;
		// if (x != 0 || (src[i] == '=' && ++j > 2) || !b64_isvalidchar(src[i]))
		// 	errors("Invalid character in input.");
		if ((src[i] == '=' && ++j > 2))
			errors("Invalid character in input.2");
		printf("I = %llu\n", i);
		if (!b64_isvalidchar(src[i]))
			errors("Invalid character in input.3");
		n++;
		i++;
	}
	n = (6 * (n >> 3)) + ((6 * (n & 0x7) + 7) >> 3);
	return (n - j);
}

static	void			treat_base_encode(char **out, char *in, t_u64 len)
{
	t_u64	i;
	t_u64	j;
	int		v;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (in[i] == '\r' || in[i] == '\n' || in[i] == ' ')
            continue;
		v = g_b64invs[in[i] - 43];
		v = (v << 6) | g_b64invs[in[i + 1] - 43];
		v = in[i + 2] == '=' ? v << 6 : (v << 6) | g_b64invs[in[i + 2] - 43];
		v = in[i + 3] == '=' ? v << 6 : (v << 6) | g_b64invs[in[i + 3] - 43];
		(*out)[j] = (v >> 16) & 0xFF;
		if (in[i + 2] != '=')
			(*out)[j + 1] = (v >> 8) & 0xFF;
		if (in[i + 3] != '=')
			(*out)[j + 2] = v & 0xFF;
		i += 4;
		j += 3;
	}
}

char					*base64_decode(char *in, t_u64 len)
{
	t_u64	outlen;
	char	*out;

	printf("LEN = %llu\nVRAI LEN = %zu\n", len, ft_strlen(in));
	outlen = size_base64_decode(in, len);
	if (!(out = malloc(outlen)))
		return (NULL);
	treat_base_encode(&out, in, len);
	out[outlen - 1] = '\0';
	return (out);
}

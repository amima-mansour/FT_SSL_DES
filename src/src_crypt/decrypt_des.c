/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrypt_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 13:12:16 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 13:13:01 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"
#include "crypt.h"

int			decrypt_base64(char **str, int len, t_des_flags *flags)
{
	char		*out;
	t_u64		outlen;

	if (flags->decrypt && flags->a)
	{
		if (!(base64_decode(*str, len, &out, &outlen)))
			return (0);
		free(*str);
		if (!(*str = ft_strnew(outlen)))
			return (0);
		ft_strncpy(*str, out, outlen);
		free(out);
	}
	return (1);
}

char		*decrypt_des(char *ct, char *key, t_des_flags *f)
{
	t_block	bk;
	t_key	k;
	int		i;
	char	*keys[16];
	char	*text;

	if (!keygen(&key) || !(split(key, &(k.left), &(k.right), 28)) || \
			!init_block(dec2bin(ct), &bk, NULL))
		return (NULL);
	i = -1;
	while (++i < 16)
		keys[i] = round_key_function(&(k.left), &(k.right), g_shift_table[i]);
	i = -1;
	while (++i < 16)
		if (!crypt_function(keys[15 - i], &bk, i))
			return (NULL);
	text = final_text(&bk, k);
	if (f->iv)
	{
		text = xor_function(text, f->iv);
		f->iv = dec2bin(ct);
	}
	return (text);
}

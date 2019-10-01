/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 13:00:53 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 14:17:58 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"
#include "crypt.h"

int				init_block(char *pt, t_block *block, char *iv)
{
	if (iv)
		pt = xor_function(pt, iv);
	pt = permute(pt, g_initial_perm, 64);
	return (split(pt, &(block->left), &(block->right), 32));
}

char			*final_text(t_block *bk, t_key k)
{
	char	*concat;

	free(k.left);
	free(k.right);
	concat = ft_strjoin(bk->left, bk->right);
	free(bk->right);
	free(bk->left);
	return (permute(concat, g_final_perm, 64));
}

int				crypt_function(char *round_key, t_block *bk, int i)
{
	char	*tmp;
	char	*op;

	if (!(tmp = ft_strdup(bk->right)))
		return (0);
	bk->right = permute(bk->right, g_exp_d, 48);
	bk->right = xor_function(round_key, bk->right);
	if (!(op = ft_strnew(32)))
		return (0);
	if (!s_boxes(bk->right, &op))
		return (0);
	op = permute(op, g_per, 32);
	bk->right = xor_function(op, bk->left);
	bk->left = tmp;
	if (i == 15)
	{
		bk->left = bk->right;
		bk->right = tmp;
	}
	return (1);
}

static int		treat_block(char **text)
{
	char	*text_block;
	int		len;

	if (!(text_block = ft_strnew(8)))
		return (0);
	len = ft_strlen(*text);
	if (len >= 8)
	{
		ft_strncpy(text_block, *text, 8);
		*text = text_block;
		return (1);
	}
	ft_strcpy(text_block, *text);
	while (len < 8)
		text_block[len++] = 8 - ft_strlen(*text);
	*text = text_block;
	return (1);
}

char			*encrypt_des(char *pt, char *key, t_des_flags *f)
{
	t_key	k;
	t_block	bk;
	int		i;
	char	*round_key;
	char	*cipher;

	if (!treat_block(&pt))
		return (NULL);
	if (!keygen(&key) || !(split(key, &(k.left), &(k.right), 28)) \
			|| !init_block(dec2bin(pt), &bk, f->iv))
		return (NULL);
	i = -1;
	while (++i < 16)
	{
		round_key = round_key_function(&(k.left), &(k.right), g_shift_table[i]);
		if (!crypt_function(round_key, &bk, i))
			return (NULL);
	}
	cipher = final_text(&bk, k);
	if (f->iv)
		f->iv = ft_strdup(cipher);
	free(pt);
	return (cipher);
}

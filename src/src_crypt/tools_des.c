/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_des.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:20:39 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 14:22:02 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"
#include "crypt.h"

char	*xor_function(char *a, char *b)
{
	size_t	i;
	char	*ans;

	if (!(ans = ft_strnew(ft_strlen(a))))
		return (NULL);
	i = -1;
	while (++i < ft_strlen(a))
	{
		if (a[i] == b[i])
			ans[i] = '0';
		else
			ans[i] = '1';
	}
	free(a);
	free(b);
	return (ans);
}

char	*permute(char *key, int *arr, int n)
{
	char	*per;
	int		i;

	if (!(per = ft_strnew(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		per[i] = key[arr[i] - 1];
	free(key);
	return (per);
}

char	*shift_left(char *k, int shifts)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	while (++i < shifts)
	{
		if (!(s = ft_strnew(28)))
			return (NULL);
		j = 0;
		while (++j < 28)
			s[j - 1] = k[j];
		s[j - 1] = k[0];
		free(k);
		k = s;
	}
	return (k);
}

int		split(char *str, char **left, char **right, int size)
{
	if (!(*left = ft_strnew(size)))
		return (0);
	if (!(*right = ft_strnew(size)))
	{
		free(*left);
		return (0);
	}
	ft_memcpy(*left, str, size);
	ft_memcpy(*right, str + size, size);
	free(str);
	return (1);
}

int		s_boxes(char *x, char **op)
{
	int		i;
	int		j;
	t_array	arr;

	i = -1;
	j = 0;
	while (++i < 8)
	{
		arr.row = 2 * (int)(x[i * 6] - '0') + (int)(x[i * 6 + 5] - '0');
		arr.col = 8 * (int)(x[i * 6 + 1] - '0') + 4 * (int)(x[i * 6 + 2] - '0')\
			+ 2 * (int)(x[i * 6 + 3] - '0') + (int)(x[i * 6 + 4] - '0');
		arr.val = g_s[i][arr.row][arr.col];
		(*op)[j] = arr.val / 8 + '0';
		arr.val %= 8;
		(*op)[j + 1] = arr.val / 4 + '0';
		arr.val %= 4;
		(*op)[j + 2] = arr.val / 2 + '0';
		arr.val %= 2;
		(*op)[j + 3] = arr.val + '0';
		j += 4;
	}
	free(x);
	return (1);
}

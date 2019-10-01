/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:34:48 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 11:05:59 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static char	*g_mp[16] =
{
	"0000", "0001", "0010", "0011",
	"0100", "0101", "0110", "0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111"
};

char		*hex2bin(char *s)
{
	char	*str;
	size_t	i;
	int		j;
	int		index;

	if (!s)
		return (s);
	if (!(str = ft_strnew(ft_strlen(s) * 4)))
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			index = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			index = s[i] - 'a' + 10;
		else
			index = s[i] - 'A' + 10;
		ft_memcpy(str + j, g_mp[index], 4);
		j += 4;
	}
	free(s);
	return (str);
}

char		*bin2dec(char *s)
{
	char	*str;
	int		j;
	int		nbr;
	int		k;
	int		i;

	if (!(str = ft_strnew(ft_strlen(s) / 8)))
		return (NULL);
	j = 0;
	nbr = 0;
	k = 0;
	i = -1;
	while (s[++i])
	{
		nbr = nbr << 1;
		if (s[i] == '1')
			nbr |= 1;
		if (++j == 8)
		{
			j = 0;
			str[k++] = nbr;
			nbr = 0;
		}
	}
	free(s);
	return (str);
}

static char	*convert_number(int n)
{
	char	*tmp;
	int		i;

	if (!(tmp = ft_strnew(8)))
		return (NULL);
	i = -1;
	while (++i < 8)
	{
		if ((n >> (7 - i)) & 1)
			tmp[i] = '1';
		else
			tmp[i] = '0';
	}
	return (tmp);
}

char		*dec2bin(char *s)
{
	char	*str;
	int		i;
	char	*tmp;
	int		j;

	if (!(str = ft_strnew(64)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < 8)
	{
		if (!(tmp = convert_number((int)s[i])))
			return (NULL);
		ft_memcpy(str + j, tmp, 8);
		j += 8;
		free(tmp);
	}
	free(s);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:33:58 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 11:07:07 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static int	convert_a_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

char		*hex2dec(char *str, int size)
{
	int		i;
	int		j;
	char	*s;
	int		nbr;

	if (!(s = (char*)malloc(size + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i <= size * 2)
	{
		nbr = convert_a_hex(str[i]);
		nbr = nbr * 16 + convert_a_hex(str[++i]);
		s[j] = nbr;
		j++;
	}
	s[size] = '\0';
	return (s);
}

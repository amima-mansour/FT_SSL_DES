/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 12:12:19 by amansour          #+#    #+#             */
/*   Updated: 2019/10/03 12:12:27 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t l1, size_t l2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = ft_strnew(l1 + l2);
	if (str)
	{
		i = 0;
		j = 0;
		while (i < l1)
		{
			str[i] = s1[i];
			++i;
		}
		while (j < l2)
		{
			str[i + j] = s2[j];
			++j;
		}
	}
	return (str);
}

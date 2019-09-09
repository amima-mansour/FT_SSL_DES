/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 10:30:50 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:25:18 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*zero_with_precision(char *s)
{
	char		*s1;
	size_t		i;

	i = 0;
	while (s[i])
		++i;
	i += 2;
	s1 = (char *)malloc(i + 1);
	s1[i] = '\0';
	s1[0] = '0';
	s1[1] = 'x';
	while (--i > 1)
		s1[i] = '0';
	return (s1);
}

char		*to_p(t_format f, va_list *ap)
{
	char		*s;
	size_t		i;

	f.flag |= ALTFLAG;
	f.mod |= LONGMOD;
	f.c = 'x';
	s = to_x(f, ap);
	if (!*s)
		return (ft_strdup("0x"));
	i = 0;
	while (s[i] && s[i] == '0')
		++i;
	if (!s[i])
	{
		if (f.p != -1)
			return (zero_with_precision(s));
		if (i <= 3)
			return (ft_strdup("0x0"));
		s[1] = 'x';
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 12:40:19 by amansour          #+#    #+#             */
/*   Updated: 2019/08/30 16:14:10 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_string(t_format f, va_list *ap)
{
	char *s;
	char *s1;

	if ((!(s = va_arg(*ap, char *)) && f.flag & LEADZEROFLAG) || f.p == 0)
		return (ft_strdup(""));
	if (!s)
		s = "(null)";
	if (f.p >= (int)ft_strlen(s) || f.p < 0)
		return (ft_strdup(s));
	s1 = (char *)malloc(f.p + 1);
	s1[f.p] = '\0';
	ft_strncpy(s1, s, f.p);
	return (s1);
}

char	*c_to_s(char c)
{
	char	*s;

	s = (char *)malloc(2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

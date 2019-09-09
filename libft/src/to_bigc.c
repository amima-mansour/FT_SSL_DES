/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bigc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:05:32 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:24:22 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_bigc(va_list *ap)
{
	wchar_t	a;
	int		len;
	char	*s;

	a = (wchar_t)va_arg(*ap, wint_t);
	if (!(len = wchar_len(a)))
		return (NULL);
	if (!(s = (char*)malloc(len + 1)))
		return (NULL);
	len = 0;
	convert_unicode(a, &s, &len);
	s[len] = '\0';
	return (s);
}

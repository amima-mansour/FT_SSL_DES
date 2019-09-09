/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_sign_decimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:23:32 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:25:29 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	to_sign_decimal(int mod, va_list *ap)
{
	if (mod & SIZETMOD)
		return (va_arg(*ap, ssize_t));
	if (mod & MAXMOD)
		return (va_arg(*ap, intmax_t));
	if (mod & LONGLONGMOD)
		return (va_arg(*ap, long long));
	if (mod & LONGMOD)
		return (va_arg(*ap, long));
	if (mod & HALFHALFMOD)
		return ((signed char)va_arg(*ap, int));
	if (mod & HALFMOD)
		return ((short)va_arg(*ap, int));
	return (va_arg(*ap, int));
}

char			*to_di(t_format f, va_list *ap)
{
	intmax_t	a;
	int			len_max;
	char		*s;

	(f.c == 'D') ? f.mod |= LONGMOD : 0;
	a = to_sign_decimal(f.mod, ap);
	len_max = MAX(length(ABS(a), 10), f.p);
	if (a >= 0)
		len_max += (f.flag & SHOWSIGNFLAG || f.flag & SPACEFLAG) ? 1 : 0;
	else
		++len_max;
	if (f.p < 0 && !(f.flag & LEFTFORMATFLAG))
		(f.flag & LEADZEROFLAG) ? len_max = MAX(len_max, f.width) : 0;
	if (!a && !f.p)
		--len_max;
	s = nbr_to_string(ABS(a), len_max, 10);
	(a >= 0 && (f.flag & SHOWSIGNFLAG)) ? s[0] = '+' : 0;
	((f.flag & SPACEFLAG) && s[0] != '+') ? s[0] = ' ' : 0;
	(a < 0) ? s[0] = '-' : 0;
	return (s);
}

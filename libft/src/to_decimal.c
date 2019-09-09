/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:21:02 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:24:51 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	to_decimal(int mod, va_list *ap)
{
	if (mod & SIZETMOD)
		return (va_arg(*ap, size_t));
	if (mod & MAXMOD)
		return (va_arg(*ap, uintmax_t));
	if (mod & LONGLONGMOD)
		return (va_arg(*ap, unsigned long long));
	if (mod & LONGMOD)
		return (va_arg(*ap, unsigned long));
	if (mod & HALFHALFMOD)
		return ((unsigned char)va_arg(*ap, unsigned int));
	if (mod & HALFMOD)
		return ((unsigned short)va_arg(*ap, unsigned int));
	return (va_arg(*ap, unsigned int));
}

char				*to_u(t_format f, va_list *ap)
{
	uintmax_t		a;
	int				len_max;

	(f.c == 'U') ? f.mod |= LONGMOD : 0;
	a = to_decimal(f.mod, ap);
	if (!a && !f.p)
		return (ft_strdup(""));
	len_max = MAX(length(a, 10), f.p);
	if (f.p < 0 && !(f.flag & LEFTFORMATFLAG))
		(f.flag & LEADZEROFLAG) ? len_max = MAX(len_max, f.width) : 0;
	return (nbr_to_string(a, len_max, 10));
}

char				*to_x(t_format f, va_list *ap)
{
	uintmax_t		a;
	int				len_max;
	char			*s;

	a = to_decimal(f.mod, ap);
	if (!a && !f.p)
		return (ft_strdup(""));
	len_max = MAX(length(a, 16), f.p);
	len_max += (f.flag & ALTFLAG && a) ? 2 : 0;
	if (f.p < 0 && !(f.flag & LEFTFORMATFLAG))
		(f.flag & LEADZEROFLAG) ? len_max = MAX(len_max, f.width) : 0;
	if (f.c == 'x')
		s = nbr_to_string(a, len_max, 16);
	else
		s = nbr_to_string(a, len_max, -16);
	if (a && f.flag & ALTFLAG)
		s[1] = f.c;
	return (s);
}

char				*to_o(t_format f, va_list *ap)
{
	uintmax_t		a;
	int				len_max;
	char			*s;

	(f.c == 'O') ? f.mod |= LONGMOD : 0;
	if (!(a = to_decimal(f.mod, ap)) && !f.p)
	{
		if (f.flag & ALTFLAG)
			return (c_to_s('0'));
		return (ft_strdup(""));
	}
	len_max = MAX(length(a, 8), f.p);
	len_max += (f.flag & ALTFLAG && a && f.p <= 0) ? 1 : 0;
	if (f.p < 0 && !(f.flag & LEFTFORMATFLAG))
		(f.flag & LEADZEROFLAG) ? len_max = MAX(len_max, f.width) : 0;
	s = nbr_to_string(a, len_max, 8);
	return (s);
}

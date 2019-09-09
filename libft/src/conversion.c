/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:13:33 by amansour          #+#    #+#             */
/*   Updated: 2019/08/30 14:14:32 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*conversion(t_format f, va_list *ap)
{
	if (f.c == 'D' || f.c == 'i' || f.c == 'd')
		return (to_di(f, ap));
	if (f.c == 'u' || f.c == 'U')
		return (to_u(f, ap));
	if (f.c == 'x' || f.c == 'X')
		return (to_x(f, ap));
	if (f.c == 'o' || f.c == 'O')
		return (to_o(f, ap));
	if (f.c == 'p')
		return (to_p(f, ap));
	if (f.c == 'c' && !(f.mod & LONGMOD))
		return (c_to_s((unsigned char)va_arg(*ap, int)));
	if (f.c == 's' && !(f.mod & LONGMOD))
		return (to_string(f, ap));
	if (f.c == 'C' || f.c == 'c')
		return (to_bigc(ap));
	return (to_bigs(f, ap));
}

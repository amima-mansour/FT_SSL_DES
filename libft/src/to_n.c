/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:22:20 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:25:01 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_n(t_format format, va_list *ap, int n)
{
	void *ptr;

	ptr = va_arg(*ap, void*);
	if (format.mod & LONGLONGMOD)
		*(long long*)ptr = n;
	else if (format.mod & LONGMOD)
		*(long*)ptr = n;
	else if (format.mod & HALFHALFMOD)
		*(signed char*)ptr = n;
	else if (format.mod & HALFMOD)
		*(short*)ptr = n;
	else if (format.mod & SIZETMOD)
		*(size_t*)ptr = n;
	else
		*(int*)ptr = n;
	return ;
}

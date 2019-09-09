/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_unicode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 14:23:56 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:20:54 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			wchar_len(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	if (wc <= 0x7FF)
		return (2);
	if (wc <= 0xFFFF)
		return (3);
	if (wc <= 0x10FFFF)
		return (4);
	return (0);
}

int			ws_len(wchar_t *wstr)
{
	int len;

	len = 0;
	while (*wstr)
	{
		len += wchar_len(*wstr);
		++wstr;
	}
	return (len);
}

void		convert_unicode(wchar_t wc, char **str, int *i)
{
	int size;

	size = wchar_len(wc);
	if (size == 1)
		(*str)[*i + 0] = wc;
	else if (size == 2)
	{
		(*str)[1 + *i] = (wc & 0x3F) + 0x80;
		(*str)[0 + *i] = (wc >> 6) + 0xC0;
	}
	else if (size == 3)
	{
		(*str)[2 + *i] = (wc & 0x3F) + 0x80;
		(*str)[1 + *i] = ((wc >> 6) & 0x3F) + 0x80;
		(*str)[0 + *i] = (wc >> 12) + 0xE0;
	}
	else
	{
		(*str)[3 + *i] = (wc & 0x3F) + 0x80;
		(*str)[2 + *i] = ((wc >> 6) & 0x3F) + 0x80;
		(*str)[1 + *i] = ((wc >> 12) & 0x3F) + 0x80;
		(*str)[0 + *i] = (wc >> 18) + 0xF0;
	}
	*i += size;
	return ;
}

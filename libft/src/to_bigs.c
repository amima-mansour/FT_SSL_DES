/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bigs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:35:30 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:24:39 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		wchar_to_write(int n, wchar_t *wstr)
{
	int i;
	int len;

	if (n < 0)
		return (ft_wstrlen(wstr));
	len = 0;
	i = -1;
	while (*wstr && len <= n)
	{
		++i;
		len += wchar_len(*wstr);
		++wstr;
	}
	return (i);
}

static int		char_to_write(int wlen, wchar_t *ws)
{
	int i;
	int a;

	i = 0;
	while (wlen-- && (a = wchar_len(*ws)))
	{
		i += a;
		++ws;
	}
	if (a)
		return (i);
	return (-1);
}

char			*to_bigs(t_format f, va_list *ap)
{
	wchar_t	*wstr;
	char	*str;
	int		wlen;
	int		len;

	if (!(wstr = va_arg(*ap, wchar_t *)))
		return (ft_strdup("(null)"));
	wlen = wchar_to_write(f.p, wstr);
	if ((len = char_to_write(wlen, wstr)) < 0)
		return (NULL);
	str = (char *)malloc(len + 1);
	len = 0;
	while (wlen--)
	{
		convert_unicode(*wstr, &str, &len);
		++wstr;
	}
	str[len] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:36:55 by amansour          #+#    #+#             */
/*   Updated: 2019/08/30 14:05:41 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		n_write(int n, char c)
{
	while (n--)
		write(1, &c, 1);
	return ;
}

int				display(char *str, t_format f)
{
	int		len;
	char	c;

	if (!(len = ft_strlen(str)) && (f.c == 'C' || f.c == 'c'))
		++len;
	if ((f.width > len) && ((f.flag & LEFTFORMATFLAG) || f.width < 0))
	{
		write(1, str, len);
		n_write((f.width - len), ' ');
	}
	else if (len < f.width)
	{
		c = (f.flag & LEADZEROFLAG) ? '0' : ' ';
		(f.p != -1 && belong(f.c, "dDiuUxXoOp") && c == '0') ? c = ' ' : 0;
		n_write(f.width - len, c);
		write(1, str, len);
	}
	else
		write(1, str, len);
	free(str);
	return (MAX(f.width, len));
}

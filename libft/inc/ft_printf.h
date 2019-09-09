/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 15:04:21 by amansour          #+#    #+#             */
/*   Updated: 2019/08/19 15:22:39 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include "libft.h"

# define LONGMOD		0x01
# define LONGLONGMOD	0x02
# define HALFMOD		0x04
# define HALFHALFMOD	0x08
# define SIZETMOD		0x10
# define MAXMOD			0x20
# define LONGDOUBLEMOD	0x40
# define ALTFLAG		0x01
# define SHOWSIGNFLAG	0x02
# define LEFTFORMATFLAG	0x04
# define SPACEFLAG		0x08
# define APOSTROPHEFLAG	0x10
# define ASTERIXFLAG	0x20
# define DOLLORFLAG		0x40
# define LEADZEROFLAG	0x80
# define CONV			"DdiuUxXoOnpCcsS"
# define OTHERS			"*#- +\'.lhjz"
# define ABS(a)			(a >= 0) ? a : -a
# define MAX(a, b)		(a > b) ? a : b

typedef struct			s_format
{
	int					flag;
	int					width;
	int					mod;
	char				c;
	int					p;
}						t_format;

/*
** ft_printf.c
*/

int						ft_printf(const char *format, ...);
int						prints(va_list *ap, char *str);
int						test(char **str, va_list *ap, int n);

/*
** util.c
*/

int						belong(char c, char *str);

/*
** conversion.c
*/

char					*conversion(t_format f, va_list *ap);
char					*to_bigc(va_list *ap);
char					*to_bigs(t_format f, va_list *ap);
char					*to_u(t_format f, va_list *ap);
char					*to_o(t_format f, va_list *ap);
char					*to_x(t_format f, va_list *ap);
char					*to_p(t_format f, va_list *ap);
char					*to_di(t_format f, va_list *ap);
void					to_n(t_format format, va_list *ap, int n);
void					to_b(t_format format, va_list *ap);

/*
** to_string.c
*/

char					*to_string(t_format f, va_list *ap);
char					*c_to_s(char c);

/*
** nbr_to_string.c
*/

int						length(uintmax_t nbr, int base);
char					*nbr_to_string(uintmax_t v, int len, int base);

/*
** test.c
*/

int						string_to_int(char **str);
int						flag(char **str);
int						modifier(char **str);

/*
** display.c
*/

int						display(char *str, t_format format);

/*
** format.c
*/
int						fill_format(char **s, t_format *format, va_list *ap);

/*
** lib
*/

int						wchar_len(wchar_t c);
int						ws_len(wchar_t *wstr);
size_t					ft_wstrlen(wchar_t *wstr);
void					convert_unicode(wchar_t c, char **s, int *i);
#endif

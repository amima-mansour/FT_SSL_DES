/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:46:26 by amansour          #+#    #+#             */
/*   Updated: 2019/08/04 12:01:19 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_hash.h"

void			init_flags(t_flags *flags)
{
	flags->r = 0;
	flags->p = 0;
	flags->s = 0;
	flags->q = 0;
	flags->error = 0;
	flags->str = NULL;
}

char			*flag_elements(int *start, t_flags *flags, char **argv)
{
	char *s;

	s = (char*)(argv[*start] + 1);
	while (*s)
	{
		if (*s == 'r')
			flags->r = 1;
		else if (*s == 'p')
			flags->p += 1;
		else if (*s == 's')
		{
			flags->s = 1;
			return (s);
		}
		else if (*s == 'q')
			flags->q = 1;
		else
		{
			flags->error = *s;
			return (NULL);
		}
		s++;
	}
	return (NULL);
}

int				flags_check(char **argv, int argc, t_flags *flags, int start)
{
	char *s;

	if (start == 1)
		init_flags(flags);
	while (++start < argc)
	{
		if (argv[start][0] != '-')
			return (start);
		s = flag_elements(&start, flags, argv);
		if (flags->s)
		{
			if (ft_strlen(s) > 1)
				flags->str = (char*)(s + 1);
			else if ((start + 1) != argc)
				flags->str = argv[++start];
			else
				flags->str = NULL;
		}
		if (flags->str || flags->error != 0)
			return (start + 1);
	}
	return (start);
}

t_u64			file_check(char *arg, char *cmd, char **str)
{
	int		fd;
	t_u64	i;

	(*str) = NULL;
	i = 0;
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		file_error(cmd, arg);
		return (0);
	}
	i = read_function(fd, str);
	close(fd);
	return (i);
}

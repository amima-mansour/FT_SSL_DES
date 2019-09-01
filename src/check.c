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

#include "ft_ssl.h"
#include "../libft/libft.h"

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

t_hash_type		cmd_check(char *s, void (**cmd)(char*, t_flags, char*, t_u64))
{
	t_hash_functions	*hash[NB_FUNCTIONS];
	int					i;

	cmd_array(hash);
	i = -1;
	while (++i < 7)
		(*hash)[i].type = DIGEST;
	i -= 1;
	while (++i < NB_FUNCTIONS)
		(*hash)[i].type = CIPHER;
	i = -1;
	while (++i < NB_FUNCTIONS)
	{
		if (ft_strcmp(s, (*hash)[i].name) == 0)
		{
			*cmd = (*hash)[i].cmd;
			return ((*hash)[i].type);
		}
	}
	cmd_error(hash, s);
	return (DIGEST);
}

t_u64			file_check(char *arg, char *cmd, char **str)
{
	char	ch;
	int		fd;
	t_u64	i;

	(*str) = NULL;
	i = 0;
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		file_error(cmd, arg);
		return (0);
	}
	while (read(fd, &ch, 1) > 0)
		i++;
	close(fd);
	(*str) = (char*)malloc(sizeof(char) * (i + 1));
	if ((fd = open(arg, O_RDONLY)) > 0)
		i = 0;
	while (read(fd, &ch, 1) > 0)
		(*str)[i++] = ch;
	(*str)[i] = '\0';
	return (i);
}

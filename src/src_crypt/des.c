/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:19:43 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 14:17:32 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static void	check_mode(char *str, t_des_flags *f)
{
	if (ft_strcmp(str, "des-ecb") == 0)
		f->mode = "ecb";
	if (ft_strcmp(str, "des-cbc") == 0)
		f->mode = "cbc";
	if (ft_strcmp(str, "des") == 0)
		f->mode = "cbc";
}

static void	check_a_flag(char *value, char *flag, t_des_flags *f)
{
	if (!ft_strcmp(flag, "-o"))
		f->out = value;
	if (!ft_strcmp(flag, "-i"))
		f->in = value;
	if (!ft_strcmp(flag, "-k"))
	{
		f->key = ft_strdup(value);
		f->key = short_key(f->key);
	}
	if (!ft_strcmp(flag, "-p"))
		f->passwd = ft_strdup(value);
	if (!ft_strcmp(flag, "-s"))
		f->salt = ft_strdup(value);
	if (!ft_strcmp(flag, "-v"))
		f->iv = ft_strdup(value);
}

static void	init_flags(t_des_flags *f)
{
	f->out = NULL;
	f->fd_in = 0;
	f->fd_out = 1;
	f->in = NULL;
	f->key = NULL;
	f->passwd = NULL;
	f->salt = NULL;
	f->iv = NULL;
	f->encrypt = 1;
	f->decrypt = 0;
	f->a = 0;
	f->tmp = NULL;
}

static void	parse_flags(char **av, int ac, t_des_flags *f)
{
	int		i;

	i = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-o") || !ft_strcmp(av[i], "-i") ||\
		!ft_strcmp(av[i], "-k") || !ft_strcmp(av[i], "-p") ||\
		!ft_strcmp(av[i], "-s") || !ft_strcmp(av[i], "-v"))
		{
			if (i + 1 >= ac)
				usage_des();
			check_a_flag(av[i + 1], av[i], f);
			i++;
		}
		else if (!ft_strcmp(av[i], "-a"))
			f->a = 1;
		else if (!ft_strcmp(av[i], "-d"))
			f->decrypt = 1;
		else if (!ft_strcmp(av[i], "-e"))
			f->encrypt = 1;
		else
			usage_des();
	}
}

void		des(int argc, char **argv)
{
	t_des_flags	flags;
	char		*str;
	int			l;

	check_mode(argv[0], &flags);
	init_flags(&flags);
	parse_flags(argv, argc, &flags);
	if (!pretreate_des(&flags, &str, &l) || !decrypt_base64(&str, l, &flags)\
			|| !ft_generate_iv_keys(&flags, &str, &l))
		return ;
	if (!flags.decrypt && !flags.a)
	{
		ft_putstr_fd(flags.tmp, flags.fd_out);
		flags.tmp = NULL;
	}
	if (!flags.decrypt && flags.a)
		encrypt_base64(flags, str, l);
	else
		crypt_des(flags, str, l);
}

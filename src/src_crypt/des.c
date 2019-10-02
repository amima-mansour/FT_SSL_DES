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
	{
		f->iv = ft_strdup(value);
		f->iv = short_key(f->iv);
	}
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

static void	clean(t_des_flags *f, char *str)
{
	if (f->passwd)
		free(f->passwd);
	free(f->key);
	if (f->iv)
		free(f->iv);
	if (f->salt)
		free(f->salt);
	if (f->tmp)
		free(f->tmp);
	free(str);
}

void		des(int argc, char **argv)
{
	t_des_flags	flags;
	char		*str;
	int			l;

	flags.mode = argv[1];
	init_flags(&flags);
	parse_flags(argv, argc, &flags);
	if (!ft_strcmp(flags.mode, "des-ecb"))
	{
		free(flags.iv);
		flags.iv = NULL;
	}
	if (!pretreat_des(&flags, &str, &l) || !decrypt_base64(&str, &l, &flags)\
			|| !ft_generate_iv_keys(&flags, &str, &l))
		return ;
	if (!hex_expr(flags.iv) || !hex_expr(flags.key))
		errors("invalid hex value");
	flags.iv = hex2bin(flags.iv);
	if (!flags.decrypt && !flags.a)
		ft_putstr_fd(flags.tmp, flags.fd_out);
	if (!flags.decrypt && flags.a)
		encrypt_base64(&flags, str, l);
	else
		crypt_des(&flags, str, l);
	clean(&flags, str);
}

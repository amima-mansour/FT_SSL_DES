/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:19:43 by amansour          #+#    #+#             */
/*   Updated: 2019/09/10 10:22:36 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ssl_crypt.h"

static void		check_mode(char *str, char **mode)
{
	if (ft_strcmp(str, "des-ecb") == 0)
		*mode = "ecb";
	if (ft_strcmp(str, "des-cbc") == 0)
		*mode = "cbc";
}

static  void	check_one_flag(char *value, char *flag, t_des_flags *f)
{
	if (!ft_strcmp(flag, "-o"))
		f->out = value;
	if (!ft_strcmp(flag, "-i"))
		f->in = value;
	if (!ft_strcmp(flag, "-k"))
		f->key = ft_strdup(value);
	if (!ft_strcmp(flag, "-p"))
		f->passwd = ft_strdup(value);
	if (!ft_strcmp(flag, "-s"))
		f->salt = ft_strdup(value);
	if (!ft_strcmp(flag, "-v"))
		f->iv = ft_strdup(value);
}

static  void	init_flags(t_des_flags *f)
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
}

static  void	parse_flags(char **av, int ac, t_des_flags *f)
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
				usage_base64();
			check_one_flag(av[i + 1], av[i], f);
			i++;
		}
		else if (!ft_strcmp(av[i], "-d"))
			f->decrypt = 1;
		else if (!ft_strcmp(av[i], "-e"))
			f->encrypt = 1;
		else
			usage_base64();
	}
}

static  void	print_flags(t_des_flags *f)
{
	ft_printf("out => %s\n", f->out);
	ft_printf("in => %s\n", f->in);
	ft_printf("fd_in => %d\n", f->fd_in);
	ft_printf("fd_out => %d\n", f->fd_out);
	ft_printf("key => %s\n", f->key);
	ft_printf("passwd => %s\n", f->passwd);
	ft_printf("salt => %s\n", f->salt);
	ft_printf("iv => %s\n", f->iv);
	ft_printf("encrypt => %d\n", f->encrypt);
	ft_printf("decrypt => %d\n", f->decrypt);
	ft_printf("tmp => %s\n", f->tmp);
}

void		des(int argc, char **argv)
{
	char		*mode;
	t_des_flags	flags;
	char		*pass;

	check_mode(argv[0], &mode);
	init_flags(&flags);
	parse_flags(argv, argc, &flags);
	if (!flags.passwd)
	{
		pass = getpass("enter des-cbc encryption password:");
		if (!(flags.passwd = ft_strdup(pass)))
			return; 
		pass = getpass("Verifying - enter des-cbc encryption password:");
		if (ft_strcmp(pass, flags.passwd))
		{
			free(flags.passwd);
			ft_putstr_fd("Verify failure\nbad password read\n", 2);
			exit(-1);
		}
	}
	ft_generate_iv_keys(&flags);
	print_flags(&flags);
	ft_printf("%s\n", algo_des(ft_strdup("AMINAMAN"), flags.key));
}

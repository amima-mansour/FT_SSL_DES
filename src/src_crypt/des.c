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
	if (ft_strcmp(str, "des") == 0)
		*mode = "cbc";
}

static  void	check_one_flag(char *value, char *flag, t_des_flags *f)
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
	if (!ft_strcmp(flag, "-a"))
		f->a = 1;
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
	f->a = 0;
	f->tmp = NULL;
}

static  void	parse_flags(char **av, int ac, t_des_flags *f)
{
	int		i;

	i = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-o") || !ft_strcmp(av[i], "-i") ||\
		!ft_strcmp(av[i], "-k") || !ft_strcmp(av[i], "-p") ||\
		!ft_strcmp(av[i], "-s") || !ft_strcmp(av[i], "-v") || \
		!ft_strcmp(av[i], "-a"))
		{
			if (i + 1 >= ac)
				usage_des();
			check_one_flag(av[i + 1], av[i], f);
			if (ft_strcmp(av[i], "-a"))
				i++;
		}
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
	char		*mode;
	t_des_flags	flags;
	char		*pass;
	char		*cipher;
	char		*str;
	int			i;
	int			len;
	char		*key;
	char		*out;
	t_u64		outlen;

	check_mode(argv[0], &mode);
	init_flags(&flags);
	parse_flags(argv, argc, &flags);
	if (!flags.passwd && !flags.key)
	{
		pass = getpass("enter des-cbc encryption password:");
		if (!(flags.passwd = ft_strdup(pass)))
			return;
		if (! (flags.decrypt))
		{
			pass = getpass("Verifying - enter des-cbc encryption password:");
			if (ft_strcmp(pass, flags.passwd))
			{
				free(flags.passwd);
				ft_putstr_fd("Verify failure\nbad password read\n", 2);
				return ;
			}
		}
		if (!ft_strlen(flags.passwd))
			return ;
	}
	if (flags.in && (flags.fd_in = open(flags.in, O_RDONLY)) == -1)
	{
		file_error("des", flags.in);
		return ;
	}
	if (flags.out && (flags.fd_out = \
				open(flags.out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		file_error("des", flags.in);
		return ;
	}
	len = read_function(flags.fd_in, &str);
	i = 0;
	if (flags.decrypt && flags.a)
	{
		if (!(base64_decode(str, len, &out, &outlen)))
			return ;
		free(str);
		if (!(str = malloc(outlen + 1)))
			return ;
		str[outlen] = '\n';
		ft_strncpy(str, out, outlen);
		free(out);
	}
	if (!ft_generate_iv_keys(&flags, &str, &len))
		return ;
	if (!flags.decrypt && !flags.a)
	{
		ft_putstr_fd(flags.tmp, flags.fd_out);
		flags.tmp = NULL;
	}
	printf("Len str = %d\n", len);
	while (i < len)
	{
		key = ft_strdup(flags.key);
		if (!flags.decrypt)
		{
			if (!(cipher = encrypt_des(str + i, key))
			return ;
			if (flags.a)
				flags.tmp = ft_strjoin(flags.tmp, bin2dec(cipher));
			else
				print_result(bin2dec(cipher), flags.fd_out);
		}
		else
		{
			if (!(cipher = decrypt_des(str + i, key))
				return ;
			print_result(bin2dec(cipher), flags.fd_out);
		}
		i += 8;
	}
	if (flags.tmp)
	{
		if (!(base64_encode(flags.tmp, ft_strlen(flags.tmp), &out, &outlen)))
			return ;
		write(1, out, outlen);
	}
}
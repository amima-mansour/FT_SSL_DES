/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:58:46 by amansour          #+#    #+#             */
/*   Updated: 2019/09/02 08:52:02 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

static void		init_flags(t_b64_flags *flags)
{
	flags->fd_in = 0;
	flags->fd_out = 1;
	flags->out = NULL;
	flags->in = NULL;
	flags->o = 0;
	flags->i = 0;
	flags->decrypt = 0;
	flags->encrypt = 0;
}

static void		read_args(t_b64_flags *f, int argc, char **argv)
{
	int i;

	init_flags(f);
	i = 1;
	while (++i < argc)
	{
		if ((!(ft_strcmp(argv[i], "-i")) || !(ft_strcmp(argv[i], "-o"))) && \
				!argv[i + 1])
			usage_base64();
		else if (!(ft_strcmp(argv[i], "-i")))
			f->in = argv[++i];
		else if (!(ft_strcmp(argv[i], "-o")))
			f->out = argv[++i];
		else if (!(ft_strcmp(argv[i], "-e")))
			f->encrypt = 1;
		else if (!(ft_strcmp(argv[i], "-d")))
			f->decrypt = 1;
	}
}

static int		check_valid_fd(t_b64_flags *flags)
{
	if (flags->in && (flags->fd_in = open(flags->in, O_RDONLY)) == -1)
	{
		file_error("base64", flags->in);
		return (0);
	}
	if (flags->out && (flags->fd_out = \
				open(flags->out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		file_error("base64", flags->in);
		return (0);
	}
	return (1);
}

void			print_base64(char *out, t_u64 outlen, int fd)
{
	int i;

	i = 0;
	while (i < (int)outlen)
	{
		ft_putchar_fd(out[i], fd);
		if (++i % 64 == 0)
			ft_putchar_fd('\n', fd);		
	}
	ft_putchar_fd('\n', fd);
}

void			base64(int argc, char **av)
{
	t_b64_flags	flags;
	uint64_t	l;
	char		*msg;
	char		*out;
	t_u64		outlen;

	read_args(&flags, argc, av);
	if (!(check_valid_fd(&flags)))
		return ;
	l = read_function(flags.fd_in, &msg);
	if ((flags.decrypt && !base64_decode(msg, l, &out, &outlen)) || \
		(!flags.decrypt && !base64_encode(msg, l, &out, &outlen)))
	{
		free(msg);
		return ;
	}
	free(msg);
	if (!flags.decrypt)
		print_base64(out, outlen, flags.fd_out);
	else
		write(flags.fd_out, out, outlen);
	free(out);
}

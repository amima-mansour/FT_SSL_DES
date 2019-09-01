/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:58:46 by amansour          #+#    #+#             */
/*   Updated: 2019/08/06 13:59:50 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

static void		read_args(t_flags *f, int argc, char **argv)
{
	int i;

	init_flags(f);
    i = 1;
	while (++i < argc)
	{
        if ((!(ft_strcmp(argv[i], "-i")) || !(ft_strcmp(argv[i], "-o"))) && !argv[i + 1])
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

void    base64(int argc, char **av)
{
    t_flags		flags;
	uint64_t	l;
    char        *msg;
    char        *final_msg;

    read_args(&flags, argc, av);
    if (flags.in && (flags.fd_in = open(flags.in, O_RDONLY)) == -1)
    {
        file_error("base64", flags.in);
        return ;
    }
    if (flags.out && (flags.fd_out = open(flags.out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
        file_error("base64", flags.in);
        return ;
    }
    l = read_stdin(flags.fd_in, &msg);
    final_msg = flags.decrypt ? base64_decode(msg, l) : base64_encode(msg, l);
	ft_putstr_fd(final_msg, flags.fd_out);
    ft_putchar_fd('\n', flags.fd_out);
    //l = flags.decrypt ? (l / 4 * 3 - (l / 4 * 3) / 64) : 
	//((l + 2) / 3 * 4 + ((l + 2) / 3 * 4) / 64);
    free(msg);
    free(final_msg);
}
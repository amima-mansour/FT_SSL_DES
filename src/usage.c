/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 10:45:42 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 10:45:49 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

void	usage(void)
{
	ft_putstr_fd("usage: ft_ssl command [command opts] [command args]\n", 2);
	exit(-1);
}

void	usage_base64(void)
{
	ft_putstr_fd("Usage:	base64 [-ed] [-i in_file] [-o out_file]\n\
	-d, decode mode\n\
	-e, encode mode (default)\n\
	-i, input file\n\
	-o, output file\n", 2);
	exit(-1);
}

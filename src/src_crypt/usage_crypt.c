/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_crypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 11:09:12 by amansour          #+#    #+#             */
/*   Updated: 2019/09/30 11:27:57 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_crypt.h"

void	usage_base64(void)
{
	ft_putstr_fd("Usage:	base64 [-ed] [-i in_file] [-o out_file]\n\
	-d, decode mode\n\
	-e, encode mode (default)\n\
	-i, input file\n\
	-o, output file\n", 2);
	exit(-1);
}

void	usage_des(void)
{
	ft_putstr_fd("Usage: des [OPTION] -k=KEY FILE\n"
	"Encrypt or Descrypt with DES.\n\n"
	" -k,      required 64bits key\n"
	" -d,      decrypt DES from input file\n"
	" -e,      encrypt DES from input file\n"
	" -a,      decode/encode the input/output in base64"
	" -o,      write result to FILE\n", 2);
	exit(-1);
}

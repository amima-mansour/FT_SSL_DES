/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:47 by amansour          #+#    #+#             */
/*   Updated: 2019/08/04 12:07:05 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_hash.h"
#include "ft_ssl_crypt.h"

int				main(int argc, char **argv)
{
	(argc < 2) ? usage() : 0;
	if (ft_strcmp(argv[1], "base64") == 0)
		base64(argc, argv);
	if (ft_strcmp(argv[1], "des-ecb") == 0)
		des(argc, argv);
	else
		cmd_hash(argc, argv, argv[1]);
	return (0);
}

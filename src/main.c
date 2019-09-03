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

#include "../libft/libft.h"
#include "ft_ssl.h"

int				main(int argc, char **argv)
{
	void		(*cmd)(char*, t_flags, char*, t_u64);
	t_hash_type type;
	char 		*str;

	(argc < 2) ? usage() : 0;
	str = argv[1];
	type = cmd_check(str, &cmd);
	if (type == DIGEST)
		treat_digest(argc, argv, cmd);
	else
	{
		if (ft_strcmp(argv[1], base64))
			base64(argc, argv);
		else
			des(argc, argv);
	}
	return (0);
}

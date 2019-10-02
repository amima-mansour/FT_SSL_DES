/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:30:58 by amansour          #+#    #+#             */
/*   Updated: 2019/10/02 13:31:19 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_hash.h"

static void	cmd_array(t_hash_functions hash[])
{
	hash[0].name = "md5";
	hash[0].cmd = &md5;
	hash[1].name = "sha256";
	hash[1].cmd = &sha256;
	hash[2].name = "sha224";
	hash[2].cmd = &sha224;
	hash[3].name = "sha512";
	hash[3].cmd = &sha512;
	hash[4].name = "sha384";
	hash[4].cmd = &sha384;
	hash[5].name = "sha512256";
	hash[5].cmd = &sha512256;
	hash[6].name = "sha512224";
	hash[6].cmd = &sha512224;
}

void		cmd_hash(int argc, char **argv, char *s)
{
	t_hash_functions	hash[NB_FUNCTIONS];
	int					i;
	void				(*cmd)(char*, t_flags, char*, t_u64);

	cmd_array(hash);
	i = -1;
	while (++i < NB_FUNCTIONS)
	{
		if (ft_strcmp(s, hash[i].name) == 0)
		{
			cmd = hash[i].cmd;
			treat_digest(argc, argv, cmd);
			return ;
		}
	}
	cmd_error(hash, s);
}

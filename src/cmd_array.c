/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 09:54:33 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 09:54:39 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

void	cmd_array(t_hash_functions *hash[])
{
	(*hash)[0].name = "md5";
	(*hash)[0].cmd = &md5;
	(*hash)[1].name = "sha256";
	(*hash)[1].cmd = &sha256;
	(*hash)[3].name = "sha512";
	(*hash)[3].cmd = &sha512;
	(*hash)[2].name = "sha224";
	(*hash)[2].cmd = &sha224;
	(*hash)[4].name = "sha384";
	(*hash)[4].cmd = &sha384;
	(*hash)[5].name = "sha512256";
	(*hash)[5].cmd = &sha512256;
	(*hash)[6].name = "sha512224";
	(*hash)[6].cmd = &sha512224;
	(*hash)[7].name = "base64";
	(*hash)[8].name = "des-ecb";
	(*hash)[9].name = "des-cbc";
}

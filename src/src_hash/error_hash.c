/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:49:44 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 09:59:22 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_hash.h"

void	cmd_error(t_hash_functions *hash[], char *cmd)
{
	int i;

	ft_putstr_fd("ft_ssl: Error: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" is an invalid command.\n\n", 2);
	ft_putstr_fd("Standard commands:\n", 2);
	ft_putstr_fd("\nMessage Digest commands:\n", 2);
	i = -1;
	while (++i < NB_FUNCTIONS)
	{
		ft_putstr_fd((*hash)[i].name, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putstr_fd("\nCipher commands:\n", 2);
	ft_putstr_fd("base64\n", 2);
	ft_putstr_fd("des-ecb\n", 2);
	ft_putstr_fd("des-cbc\n", 2);
	exit(-1);
}

void	flag_error(char c, char *cmd)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ft_ssl ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" [-pqr] [-s string] [files ...]\n", 2);
	exit(-1);
}

void	s_error(char *cmd)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": option requires an argument -- s\nusage: ft_ssl ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" [-pqr] [-s string] [files ...]\n", 2);
	exit(-1);
}

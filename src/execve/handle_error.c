/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:44:59 by saan              #+#    #+#             */
/*   Updated: 2025/09/16 12:24:06 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_open_error(char *name)
{
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

void	write_access_error(char *name, int err)
{
	write(2, "bash: ", 6);
	write(2, name + 1, ft_strlen(name + 1));
	write(2, ": ", 2);
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	if (err == ENOENT)
	{
		// write(2, "Command not found\n", 18);
		exit(127);
	}
	else if (err == EACCES)
	{
		// write(2, "Permission denied\n", 18);
		exit(126);
	}
	else if (err == ENOTDIR)
	{
		// write(2, "Not a directory\n", 16);
		exit(126);
	}
}

void	write_cmd_nf(char *name)
{
	// write(2, "bash: ", 6);
	write(2, name + 1, ft_strlen(name + 1));
	write(2, ": ", 2);
	write(2, "Command not found\n", 18);
	exit(127);
}

void	exit_with_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

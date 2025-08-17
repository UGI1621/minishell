/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:44:59 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 16:21:45 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_open_error(char *name)
{
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	strerror(errno);
	g_sigs.exit_code = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	write_access_error(char *name)
{
	int	exit_code;

	exit_code = 1;
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	if (errno == ENOENT)
	{
		write(2, "command not found\n", 18);
		g_sigs.exit_code = 127;
		exit_code = 127;
	}
	else if (errno == EACCES)
	{
		write(2, "permission denied\n", 18);
		g_sigs.exit_code = 126;
		exit_code = 126;
	}
	else if (errno == ENOTDIR)
	{
		write(2, "not a directory\n", 16);
		g_sigs.exit_code = 126;
		exit_code = 126;
	}
	free(--name);
	exit(exit_code);
}

void	exit_with_perror(char *str)
{
	perror(str);
	g_sigs.exit_code = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

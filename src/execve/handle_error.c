/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:44:59 by saan              #+#    #+#             */
/*   Updated: 2025/09/10 06:45:38 by saan             ###   ########.fr       */
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
	g_sigs.exit_code = EXIT_FAILURE;
}

void	write_access_error(char *name)
{
	write(2, name + 1, ft_strlen(name + 1));
	write(2, ": ", 2);
	if (errno == ENOENT)
	{
		write(2, "command not found\n", 18);
		g_sigs.exit_code = 127;
	}
	else if (errno == EACCES)
	{
		write(2, "permission denied\n", 18);
		g_sigs.exit_code = 126;
	}
	else if (errno == ENOTDIR)
	{
		write(2, "not a directory\n", 16);
		g_sigs.exit_code = 126;
	}
	free(name);
}

void	exit_with_perror(char *str)
{
	perror(str);
	g_sigs.exit_code = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

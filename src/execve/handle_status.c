/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 05:03:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/10 00:13:06 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status(int status)
{
	if (WIFEXITED(status))
		g_sigs.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sigs.exit_code = 128 + WTERMSIG(status);
}

void	set_heredoc_status(int status)
{
	if (WIFEXITED(status))
	{
		g_sigs.exit_code = WEXITSTATUS(status);
		if (WEXITSTATUS(status) == 130)
			g_sigs.heredoc_sigint = 1;
	}
}

void	check_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	}
}

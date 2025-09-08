/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:19:56 by saan              #+#    #+#             */
/*   Updated: 2025/09/08 04:56:21 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_sigs(void)
// {
// 	if (signal(SIGINT, s_sigint_handler) == SIG_ERR)
// 	{
// 		perror("signal SIGINT");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 	{
// 		perror("signal SIGQUIT");
// 		exit(EXIT_FAILURE);
// 	}
// }


// void	s_sigint_handler(int signum)
// {
// 	(void)signum;

// 	g_sigs.exit_code = 130;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// }

void	sigint_handler(int signum)
{
	(void)signum;

	g_sigs.exit_code = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

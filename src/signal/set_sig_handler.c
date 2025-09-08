/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:17:45 by saan              #+#    #+#             */
/*   Updated: 2025/09/08 05:40:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal SIGINT handler");
		exit(EXIT_FAILURE);
	}
}

void	set_sigquit_handler(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal SIGQUIT SIG_IGN");
		exit(EXIT_FAILURE);
	}
}

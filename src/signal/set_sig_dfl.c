/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_dfl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:38:57 by saan              #+#    #+#             */
/*   Updated: 2025/09/08 05:41:46 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint_dfl(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("signal SIGINT SIG_DFL");
		exit(EXIT_FAILURE);
	}
}

void	set_sigquit_dfl(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("signal SIGQUIT SIG_DFL");
		exit(EXIT_FAILURE);
	}
}

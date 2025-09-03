/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 05:03:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/02 05:05:20 by saan             ###   ########.fr       */
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

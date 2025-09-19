/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:01:48 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 01:36:40 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_status(pid_t *pid, int *status, int i)
{
	set_sigs_ign();
	waitpid(pid[i], status, 0);
	set_sigs();
	set_status((*status));
}

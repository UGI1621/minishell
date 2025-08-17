/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:06:39 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 09:17:07 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infiles(char **infile)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (infile[++i])
	{
		if (fd != -1)
			close(fd);
		fd = open(infile[i], O_RDONLY);
		if (fd == -1)
			write_open_error(infile[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:31:24 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:23:09 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_write_open_error(char *name)
{
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

int	b_open_infiles(char **files, char **in_sig)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (files[++i])
	{
		if (!ft_strcmp(in_sig[i], "<<"))
			continue ;
		if (fd != -1)
			close(fd);
		fd = open(files[i], O_RDONLY);
		if (fd == -1)
		{
			b_write_open_error(files[i]);
			return (-1);
		}
	}
	return (fd);
}

int	b_open_outfiles(char **files, char **sigs)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (files[++i])
	{
		if (fd != -1)
			close(fd);
		if (!ft_strcmp(sigs[i], ">"))
			fd = open(files[i], O_RDWR | O_CREAT | O_TRUNC, 0664);
		else
			fd = open(files[i], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
		{
			b_write_open_error(files[i]);
			return (-1);
		}
	}
	return (fd);
}

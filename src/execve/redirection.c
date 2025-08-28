/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:06:39 by saan              #+#    #+#             */
/*   Updated: 2025/08/25 16:43:03 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infiles(char **files)
{
	int	i;
	int	fd;

	i = -1;

	fd = -1;
	while (files[++i])
	{
		if (fd != -1)
			close(fd);
		fd = open(files[i], O_RDONLY);
		if (fd == -1)
			write_open_error(files[i]);
	}
	return (fd);
}

int	open_outfiles(char **files, char **sigs)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (files[++i])
	{
		if (fd != -1)
			close(fd);
		if (!ft_strncmp(sigs[i], ">", ft_strlen(sigs[i])))
			fd = open(files[i], O_RDWR | O_CREAT | O_TRUNC, 0664);
		else
			fd = open(files[i], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			write_open_error(files[i]);
	}
	return (fd);
}

void	set_node_fds(t_cmd_node *node)
{
	if (node->prev)
	{
		close(node->prev->pipe[1]);
		dup2(node->prev->pipe[0], STDIN_FILENO);
	}
	if (node->next)
	{
		close(node->pipe[0]);
		dup2(node->pipe[1], STDOUT_FILENO);
	}
	if (node->is_use_heredoc)
	{
		// node->in_fd = node->heredoc_fd;
		node->in_fd = open("heredoc_temp", O_RDONLY);
	}
	else
		node->in_fd = open_infiles(node->infile);
	if (node->in_fd != -1)
		dup2(node->in_fd, STDIN_FILENO);
	node->out_fd = open_outfiles(node->outfile, node->out_sig);
	if (node->out_fd != -1)
		dup2(node->out_fd, STDOUT_FILENO);
}

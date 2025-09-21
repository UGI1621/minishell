/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 09:06:39 by saan              #+#    #+#             */
/*   Updated: 2025/09/21 14:27:40 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infiles(t_cmd_node *node, t_cmd_list *list, t_env_list *my_env)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (node->infile[++i])
	{
		if (!ft_strcmp(node->in_sig[i], "<<"))
			continue ;
		if (fd != -1)
			close(fd);
		fd = open(node->infile[i], O_RDONLY);
		if (fd == -1)
			write_open_error(node->infile[i], list, my_env);
	}
	return (fd);
}

int	open_outfiles(char **files, char **sigs, t_cmd_list *list,
		t_env_list *my_env)
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
			write_open_error(files[i], list, my_env);
	}
	return (fd);
}

static void	set_nodes_pipe(t_cmd_node *node)
{
	if (node->prev)
	{
		close(node->prev->pipe[1]);
		dup2(node->prev->pipe[0], STDIN_FILENO);
		close(node->prev->pipe[0]);
	}
	if (node->next)
	{
		close(node->pipe[0]);
		dup2(node->pipe[1], STDOUT_FILENO);
		close(node->pipe[1]);
	}
	else
	{
		close(node->pipe[0]);
		close(node->pipe[1]);
	}
}

void	set_node_fds(t_cmd_node *node, t_cmd_list *list, t_env_list *my_env)
{
	set_nodes_pipe(node);
	if (node->is_use_heredoc)
		node->in_fd = open("heredoc_temp", O_RDONLY);
	else
		node->in_fd = open_infiles(node, list, my_env);
	if (node->in_fd != -1)
	{
		dup2(node->in_fd, STDIN_FILENO);
		close(node->in_fd);
	}
	node->out_fd = open_outfiles(node->outfile, node->out_sig, list, my_env);
	if (node->out_fd != -1)
	{
		dup2(node->out_fd, STDOUT_FILENO);
		close(node->out_fd);
	}
}

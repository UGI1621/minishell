/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:02:02 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 17:02:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		list_size(t_dllist *list)
{
	t_cmd_node *node;
	int			i;

	i = 0;
	node = list->head;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	child_process(t_cmd_node *node, pid_t *pid, char **env)
{
	free(pid);
	set_node_fds(node);
	check_and_set_argv(node);
	if (execve(node->argv[0], node->argv, env) == -1)
	{
		perror(node->argv[0]);
		exit(126);
	}
}

void	parent_process(t_cmd_node *node)
{
	if (node->prev)
	{
		close(node->prev->pipe[0]);
		close(node->prev->pipe[1]);
	}
	if (!node->next)
	{
		close(node->pipe[0]);
		close(node->pipe[1]);
	}
}

static void	do_cmd(pid_t *pid, t_cmd_node *node, int size, char **env)
{
	int			i;
	int			status;

	i = -1;
	while (++i < size)
	{
		// if (is_builtin(node->argv[0]))
		// 	continue ;
		if (pipe(node->pipe) == -1)
			exit_with_perror("pipe");
		pid[i] = fork();
		if (pid[i] < 0)
			exit_with_perror("fork");
		if (pid[i] == 0)
			child_process(node, pid, env);
		parent_process(node);
		node = node->next;
	}
	i = -1;
	while (++i < size)
		waitpid(pid[i], &status, 0);
}

void	process_cmd_exe(t_dllist *list, char **env)
{
	pid_t	*pid;
	int		size;

	size = list_size(list);
	if (!size)
		return ;
	pid = (pid_t *)ft_calloc(size, sizeof(pid_t));
	// if (size == 1 && is_builtint(list->head->argv[0]))
	// 	do_builtin();
	// else
		do_cmd(pid, list->head, size, env);
	free(pid);
}

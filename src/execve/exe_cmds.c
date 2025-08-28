/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:02:02 by saan              #+#    #+#             */
/*   Updated: 2025/08/28 17:40:56 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		list_size(t_cmd_list *list)
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

static void	child_process(t_cmd_node *node, pid_t *pid, t_env_list *my_env)
{
	char	**envp;

	envp = env_to_envp(my_env);
	free(pid);
	set_node_fds(node);
	if (is_builtin(node))
	{
		do_builtin(node, 0);
		exit(1);
	}
	check_and_set_argv(node);
	if (execve(node->cmd_path, node->argv, envp) == -1)
	{
		perror(node->argv[0]);
		exit(126);
	}
}

static void	parent_process(t_cmd_node *node)
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

static void	do_cmd(pid_t *pid, t_cmd_node *node, int size, t_env_list *my_env)
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
			child_process(node, pid, my_env);
		parent_process(node);
		node = node->next;
	}
	i = -1;
	while (++i < size)
		waitpid(pid[i], &status, 0);
}

void	process_cmd_exe(t_cmd_list *list, t_env_list *my_env)
{
	pid_t	*pid;
	int		size;

	size = list_size(list);
	if (!size)
		return ;
	pid = (pid_t *)ft_calloc(size, sizeof(pid_t));
	if (size == 1 && is_builtin(list->head))
		do_builtin(list->head, 1);
	else
		do_cmd(pid, list->head, size, my_env);
	free(pid);
}

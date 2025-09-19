/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:23:38 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:48:52 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_got_quote(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (1);
	else
		return (0);
}

static void	do_heredoc(t_cmd_node *node, int *idx, t_cmd_list *list,
		t_env_list *my_env)
{
	char	*del;

	del = remove_quotes(ft_strdup(node->infile[(*idx)]));
	heredoc_proc(del, node->heredoc_fd, is_got_quote(node->infile[(*idx)]),
		my_env);
	close(node->heredoc_fd);
	free(del);
	free_cmd_list(list, NULL);
	env_free(my_env);
	exit(g_exit_code);
}

static void	parent_heredoc(t_cmd_node *node, pid_t pid, int *status,
		int *heredoc_sigint)
{
	set_sigs_ign();
	waitpid(pid, status, 0);
	set_heredoc_status(*status, heredoc_sigint);
	set_sigs();
	close(node->heredoc_fd);
}

void	do_heredoc_process(t_cmd_list *list, t_env_list *my_env,
		int *heredoc_sigint)
{
	t_cmd_node	*node;
	int			i;
	int			status;
	pid_t		pid;

	node = list->head;
	while (node)
	{
		i = -1;
		while (node->in_sig[++i])
		{
			if (!ft_strcmp(node->in_sig[i], "<<"))
			{
				set_heredoc_fd(node);
				pid = fork();
				if (pid == 0)
					do_heredoc(node, &i, list, my_env);
				else
					parent_heredoc(node, pid, &status, heredoc_sigint);
				if (*heredoc_sigint)
					return ;
			}
		}
		node = node->next;
	}
}

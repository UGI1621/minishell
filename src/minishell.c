/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/09/10 08:22:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigs g_sigs;
// valgrind --leak-check=full --show-leak-kinds=all --trace-children=no --child-silent-after-fork=yes --suppressions=readline.supp ./minishell
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=no --child-silent-after-fork=yes --suppressions=readline.supp ./minishell
// cat << 1 << 2 | cat djqtsmsvkdlf.txt | echo "'"$HOME

void	print_lexing_list(t_lexer_list *list)
{
	t_lexer_node	*node;

	node = list->head;
	printf("node : ");
	while(node)
	{
		printf("[%s]->", node->str);
		node = node->next;
	}
	printf("\n");
}

void	print_cmd_list(t_cmd_list *list)
{
	t_cmd_node *node;

	node = list->head;
	printf("\nCMD NODES\n");
	while(node)
	{
		printf("node info \n");
		printf("node->argv : ");
		int i = -1;
		while (node->argv && node->argv[++i])
			printf("{%s} ", node->argv[i]);
		i = -1;
		printf("\nnode->infile : ");
		while (node->infile && node->infile[++i])
			printf("{%s} ", node->infile[i]);
		printf("\nnode->in_fd : %d", node->in_fd);
		i = -1;
		printf("\nnode->outfile : ");
		while (node->outfile && node->outfile[++i])
			printf("{%s} ", node->outfile[i]);
		i = -1;
		printf("\nnode->out_sig : ");
		while (node->out_sig && node->out_sig[++i])
			printf("{%s} ", node->out_sig[i]);
		printf("\nnode->out_fd : %d\n", node->out_fd);
		printf("node->is_use_heredoc : %d\n", node->is_use_heredoc);
		printf("pipe[0] : %d\npipe[1] : %d\n\n",node->pipe[0], node->pipe[1]);
		node = node->next;
	}
}

static char	*ft_readline()
{
	char *line;

	line = readline("minishell> ");
	if (!line)
	{
		write(1,"exit\n", 5);
		g_sigs.exit_code = 0;
		return (0);
	}
	if (!ft_strcmp(line, "exit"))
	{
		ft_putendl_fd("Exiting minishell...", 1);
		free(line);
		rl_clear_history();
		g_sigs.exit_code = 0;
		return (0);
	}
	if (ft_strlen(line) == 0)
		return (line);
	add_history(line);
	return (line);
}

static void	lexing_listing(char *line, t_env_list *my_env)
{
	t_lexer_list	*lexing_list;
	t_cmd_list	*cmd_list;

	if (is_invalid_line(line))
	{
		g_sigs.exit_code = 2;
		return ;
	}
	lexing_list = ft_lexing(line);
	if (!lexing_list)
	{
		g_sigs.exit_code = 2;
		return ;
	}
	print_lexing_list(lexing_list);
	cmd_list = listing_cmd(lexing_list, my_env);
	print_cmd_list(cmd_list);
	free_lexer_list(lexing_list);
	if (g_sigs.heredoc_sigint)
	{
		g_sigs.heredoc_sigint = 0;
		return ;
	}
	process_cmd_exe(cmd_list, my_env);
	free_cmd_list(cmd_list);
}

int	main(int _ac, char **_av, char **env)
{
	char	*line;
	char	*temp;
	(void)_ac;
	(void)_av;
	t_env_list	*my_env;

	g_sigs.exit_code = 0;
	g_sigs.heredoc_sigint = 0;
	set_sigs();
	envp_to_env(&my_env, env);
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		if (line && line[0] == 0)
			continue ;
		temp = ft_strdup(line);
		free(line);
		lexing_listing(temp, my_env);
		free(temp);
	}
	env_free(my_env);
	return (g_sigs.exit_code);
}

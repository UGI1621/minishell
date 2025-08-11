/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/08/11 10:29:34 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigs g_sigs;
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

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

void	print_cmd_list(t_dllist *list)
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
			printf(" %s", node->argv[i]);
		printf("\nnode->infile : %s\n", node->infile);
		printf("node->in_fd : %d\n", node->in_fd);
		printf("node->append_out : %d\n", node->append_out);
		printf("node->outfile : %s\n", node->outfile);
		printf("node->out_fd : %d\n", node->out_fd);
		printf("node->heredoc_delim : %s\n", node->heredoc_delim);
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
		return (0);
	}
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		ft_putendl_fd("Exiting minishell...\n", 1);
		free(line);
		rl_clear_history();
		return (NULL);
	}
	if (ft_strlen(line) == 0)
		return (line);
	add_history(line);
	return (line);
}

static int	lexing_listing(char *line)
{
	t_lexer_list	*lexing_list;
	t_dllist	*cmd_list;

	if (is_invalid_line(line))
	{
		g_sigs.exit_code = 2;
		return (1);
	}
	lexing_list = ft_lexing(line);
	if (!lexing_list)
	{
		g_sigs.exit_code = 2;
		return (1);
	}
	print_lexing_list(lexing_list);
	cmd_list = listing_cmd(lexing_list);
	print_cmd_list(cmd_list);
	free_lexer_list(lexing_list);
	return (0);
}

int	main(void)
{
	char	*line;
	char	*temp;

	init_sigs();
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		temp = ft_strdup(line);
		free(line);
		if (lexing_listing(temp))
			continue ;
		printf("you entered : %s\n", temp);
		free(temp);
	}
	return (0);
}

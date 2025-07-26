/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/07/27 06:25:35 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigs g_sigs;
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

void	print_lexing_list(t_lexer_list *list)
{
	t_lexer_node	*node;

	node = list->head;
	while(node)
	{
		printf("node->str : %s\n", node->str);
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

static int	mini_process(char *line)
{
	t_lexer_list	*lexing_list;

	if (is_invalid_line(line))
	{
		g_sigs.exit_code = 2;
		return (1);
	}
	lexing_list = ft_lexing(line);
	print_lexing_list(lexing_list);
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
		if (mini_process(temp))
			continue ;
		printf("you entered : %s\n", temp);
		free(temp);
	}
	return (0);
}

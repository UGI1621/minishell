/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/07/24 14:00:46 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigs g_sigs;
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

static char	*ft_readline()
{
	char *line;

	line = readline("minishell> ");
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
	char *cmd;

	if (open_quote(line))
	{
		write(1, "minishell: syntax error with open quotes or backslash\n", 55);
		g_sigs.exit_code = 1;
		return (1);
	}
	cmd = normalize_cmd(line);
	printf("normalized line : %s\n", cmd);
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

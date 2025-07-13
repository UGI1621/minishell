/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/07/13 17:37:07 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

char	*ft_readline()
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

int	main(void)
{
	char *line;

	while (1)
	{
		line = ft_readline();
		char *temp = ft_strdup(line);
		if (!line)
			break ;
		printf("you entered : %s\n", line);
		free(line);
	}
	return (0);
}

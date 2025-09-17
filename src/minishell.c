/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 13:06:07 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigs		g_sigs;

static char	*ft_readline(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (!ft_strcmp(line, "exit"))
	{
		ft_putendl_fd("Exiting minishell...", 1);
		free(line);
		rl_clear_history();
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
	t_cmd_list		*cmd_list;

	if (is_invalid_line(line))
	{
		free(line);
		return ;
	}
	lexing_list = ft_lexing(line, my_env);
	free(line);
	if (!lexing_list)
	{
		g_sigs.exit_code = 2;
		return ;
	}
	cmd_list = listing_cmd(lexing_list, my_env);
	free_lexer_list(lexing_list);
	if (g_sigs.heredoc_sigint)
	{
		g_sigs.heredoc_sigint = 0;
		free_cmd_list(cmd_list);
		return ;
	}
	process_cmd_exe(cmd_list, my_env);
	free_cmd_list(cmd_list);
}

int	invalid_ac(void)
{
	ft_putendl_fd("Invalid argc", 2);
	ft_putendl_fd("Usage: ./minishell", 2);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*temp;
	t_env_list	*my_env;

	(void)av;
	if (ac != 1)
		return (invalid_ac());
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
	}
	env_free(my_env);
	return (g_sigs.exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:30:30 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:46:36 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_code;

static char	*ft_readline(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strlen(line) == 0)
		return (line);
	add_history(line);
	return (line);
}

static int	pre_listing_cmd(char *line, t_lexer_list **lexing_list,
		t_env_list *my_env)
{
	if (is_invalid_line(line))
	{
		free(line);
		return (1);
	}
	*lexing_list = ft_lexing(line, my_env);
	free(line);
	if (!(*lexing_list))
	{
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

static void	lexing_listing(char *line, t_env_list *my_env)
{
	t_lexer_list	*lexing_list;
	t_cmd_list		*cmd_list;
	int				heredoc_sigint;

	heredoc_sigint = 0;
	if (pre_listing_cmd(line, &lexing_list, my_env))
		return ;
	cmd_list = listing_cmd(lexing_list);
	free_lexer_list(lexing_list);
	g_exit_code = 0;
	do_heredoc_process(cmd_list, my_env, &heredoc_sigint);
	if (heredoc_sigint)
	{
		free_cmd_list(cmd_list, "heredoc_temp");
		return ;
	}
	process_cmd_exe(cmd_list, my_env);
	free_cmd_list(cmd_list, "heredoc_temp");
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
	g_exit_code = 0;
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
	return (g_exit_code);
}

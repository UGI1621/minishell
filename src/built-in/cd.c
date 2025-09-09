/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:52:09 by saan              #+#    #+#             */
/*   Updated: 2025/09/10 01:34:25 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_home(int save_stdin, int save_stdout, t_env_list *my_env)
{
	char	*old;

	if (!get_env("HOME", my_env))
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	else
	{
		old = getcwd(NULL, 0);
		if (chdir(get_env("HOME", my_env)) == -1)
		{
			free(old);
			return (print_error_path(ft_strdup(get_env("HOME", my_env)), save_stdin, save_stdout));
		}
		else
		{
			update_pwds(getcwd(NULL, 0), old, my_env);
			return (0);
		}
	}
}

static int	ft_cd_path(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env)
{
	char	*old;
	char	*path;

	path = parsing_path(node->argv[1], my_env);
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	old = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(old);
		return (print_error_path(path, save_stdin, save_stdout));
	}
	else
	{
		free(path);
		update_pwds(getcwd(NULL, 0), old, my_env);
		set_iofds(save_stdin, save_stdout);
		return (0);
	}
}

static int	ft_cd_back(int save_stdin, int save_stdout, t_env_list *my_env)
{
	char	*old;

	old = getcwd(NULL, 0);
	if (chdir(get_env("OLDPWD", my_env)) == -1)
	{
		free(old);
		return (print_error_path(ft_strdup(get_env("OLDPWD", my_env)), save_stdin, save_stdout));
	}
	else
	{
		update_pwds(getcwd(NULL, 0), old, my_env);
		set_iofds(save_stdin, save_stdout);
		return (0);
	}
	return (0);
}

int	ft_cd(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env)
{
	int	i;

	i = 0;
	while (node->argv[i])
		i++;
	if (i >= 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	if (i == 1)
		return (ft_cd_home(save_stdin, save_stdout, my_env));
	if (i == 2)
	{
		if (!ft_strcmp(node->argv[1], "~"))
			return (ft_cd_home(save_stdin, save_stdout, my_env));
		else if (!ft_strcmp(node-> argv[1], "-"))
			return (ft_cd_back(save_stdin, save_stdout, my_env));
		else
			return (ft_cd_path(node, save_stdin, save_stdout, my_env));
	}
	set_iofds(save_stdin, save_stdout);
	return (0);
}

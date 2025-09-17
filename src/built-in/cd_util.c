/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:20:09 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 17:57:26 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwds(char *cur, char *old, t_env_list *my_env)
{
	int	set_flag;

	set_flag = 1;
	set_env("OLDPWD", old, &set_flag, my_env);
	set_env("PWD", cur, &set_flag, my_env);
	free(cur);
	free(old);
}

int	print_error_path(char *path, int save_stdin, int save_stdout)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	set_iofds(save_stdin, save_stdout);
	free(path);
	return (1);
}

char	*parsing_path(char *str, t_env_list *my_env)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	if (str[i] == '~')
	{
		if (get_env("HOME", my_env))
			res = ft_strjoin_af(res, ft_strdup(get_env("HOME", my_env)));
		else
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	while (str[i])
	{
		res = append_char(res, str[i]);
		i++;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:07:08 by saan              #+#    #+#             */
/*   Updated: 2025/09/18 10:03:49 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_invalid_export(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		i++;
	if (i < 2)
	{
		ft_putendl_fd("minishell: export: too few arguments", 2);
		return (1);
	}
	return (0);
}

void	print_invalid_export(char *arg, int *flag)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*flag = 1;
}

static char	*get_argv_key(char *str)
{
	char	*ptr;
	char	*temp;
	char	*res;

	temp = ft_strdup(str);
	ptr = ft_strchr(temp, '=');
	if (ptr)
		*ptr = 0;
	res = ft_strdup(temp);
	free(temp);
	return (res);
}

static char	*get_argv_val(char *str, int *set_flag)
{
	char	*ptr;
	char	*temp;
	char	*res;

	temp = ft_strdup(str);
	ptr = ft_strchr(temp, '=');
	if (ptr)
	{
		ptr++;
		if (!(*ptr))
			res = ft_strdup("");
		else
			res = ft_strdup(ptr);
		free(temp);
		*set_flag = 1;
		return (res);
	}
	else
	{
		*set_flag = 0;
		free(temp);
		return (ft_strdup(""));
	}
}

int	ft_export(t_cmd_node *node, int save_stdin, int save_stdout,
		t_env_list *my_env)
{
	int		i;
	int		flag;
	int		set_flag;
	char	*temp_key;
	char	*temp_val;

	flag = 0;
	if (is_invalid_export(node->argv))
		return (1);
	i = 0;
	while (node->argv[++i])
	{
		if (is_invalid_env_naming_rule(node->argv[i]))
		{
			print_invalid_export(node->argv[i], &flag);
			continue ;
		}
		temp_key = get_argv_key(node->argv[i]);
		temp_val = get_argv_val(node->argv[i], &set_flag);
		set_env(temp_key, temp_val, &set_flag, my_env);
		free(temp_key);
		free(temp_val);
	}
	set_iofds(save_stdin, save_stdout);
	return (flag);
}

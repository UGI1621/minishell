/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:52:09 by saan              #+#    #+#             */
/*   Updated: 2025/09/04 00:57:04 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_cd_home(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env)
// {
// 	if (!is_env_key("HOME"))
// 	{
// 		ft_putendl_fd("minishell: cd: HOME not set", 2);
// 		set_iofds(save_stdin, save_stdout);
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_cd(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env)
// {
// 	int	i;

// 	i = 0;
// 	while (node->argv[i])
// 		i++;
// 	if (i >= 3)
// 	{
// 		ft_putendl_fd("minishell: cd: too many arguments", 2);
// 		set_iofds(save_stdin, save_stdout);
// 		return (1);
// 	}
// 	if (i == 1)
// 		return (ft_cd_home(node, save_stdin, save_stdout, my_env));
// 	if (i == 2)
// 	{

// 	}
// 	return (0);
// }

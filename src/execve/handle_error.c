/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:44:59 by saan              #+#    #+#             */
/*   Updated: 2025/09/21 14:56:15 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_open_error(char *name, t_cmd_list *list, t_env_list *my_env)
{
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	free_cmd_list(list, NULL);
	env_free(my_env);
	exit(1);
}

void	write_is_dir(DIR *dir, char *name, t_cmd_list *list, t_env_list *my_env)
{
	closedir(dir);
	write(2, "bash: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	ft_putstr_fd("is a directory", 2);
	write(2, "\n", 1);
	free_cmd_list(list, NULL);
	env_free(my_env);
	free(name);
	exit(126);
}

void	write_access_error(char *name, t_cmd_list *list, t_env_list *my_env)
{
	write(2, "bash: ", 6);
	write(2, name + 1, ft_strlen(name + 1));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	free(name);
	free_cmd_list(list, NULL);
	env_free(my_env);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else if (errno == ENOTDIR)
		exit(126);
}

void	write_cmd_nf(char *name, t_cmd_list *list, t_env_list *my_env)
{
	write(2, name + 1, ft_strlen(name + 1));
	write(2, ": ", 2);
	write(2, "Command not found\n", 18);
	free(name);
	free_cmd_list(list, NULL);
	env_free(my_env);
	exit(127);
}

void	exit_with_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

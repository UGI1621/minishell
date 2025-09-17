/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extending_util.c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:06:46 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 18:49:47 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable(char *str)
{
	if (str[0] == '?' || str[0] == '$' || str[0] == '!' || str[0] == '-'
		|| str[0] == '#' || str[0] == '*' || str[0] == '@')
		return (1);
	if (ft_isdigit(str[0]))
		return (1);
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	return (0);
}

char	*no_extend_res(char *s)
{
	char	*res;

	res = ft_strdup("$");
	res = ft_strjoin_af(res, s);
	return (res);
}

char	*extend_res(char *s, t_env_list *my_env)
{
	char	*temp;

	if (ft_strlen(s) == 1 && !ft_strcmp(s, "?"))
	{
		free(s);
		return (ft_itoa(g_exit_code));
	}
	temp = get_env(s, my_env);
	if (!temp)
	{
		temp = ft_strdup("");
		free(s);
		return (temp);
	}
	free(s);
	return (ft_strdup(temp));
}

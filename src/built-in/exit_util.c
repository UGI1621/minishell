/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:38:40 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 21:35:02 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_need_digit_nof(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (2);
}

int	is_out_of_longlong(const char *s)
{
	int			sign;
	int			len;
	const char	*num;

	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == '0')
		s++;
	num = s;
	len = strlen(num);
	if (len == 0 || strspn(num, "0123456789") != (size_t)len)
		return (1);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == 1)
		return (strcmp(num, "9223372036854775807") > 0);
	else
		return (strcmp(num, "9223372036854775808") > 0);
}

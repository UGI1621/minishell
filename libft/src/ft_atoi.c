/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:37:35 by saan              #+#    #+#             */
/*   Updated: 2024/10/29 19:50:31 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_sign_check(char c, int *sign_cnt, int *ismin)
{
	if (c == '-')
	{
		*sign_cnt += 1;
		*ismin = 1;
		return (1);
	}
	if (c == '+')
	{
		*sign_cnt += 1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	res;
	int		sign_cnt;
	int		ismin;

	res = 0;
	sign_cnt = 0;
	ismin = 0;
	while (ft_isspace(*nptr))
		nptr++;
	while (ft_sign_check(*nptr, &sign_cnt, &ismin))
		nptr++;
	if (sign_cnt >= 2)
		return (0);
	while (ft_isdigit(*nptr))
	{
		res = (10 * res) + (*nptr - '0');
		nptr++;
	}
	if (ismin)
		return ((int)(-res));
	return ((int)res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:40:04 by saan              #+#    #+#             */
/*   Updated: 2024/12/30 05:43:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(long long n)
{
	int	res;

	if (n == 0)
		return (1);
	res = 0;
	while (n != 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

static void	ft_do_itoa(char *res, long long *num, int *len, int *is_min)
{
	if (*is_min)
		*num = -(*num);
	while ((*len)-- > 0)
	{
		res[*len] = (*num % 10) + '0';
		*num /= 10;
	}
	if (*is_min)
		res[0] = '-';
}

char	*ft_itoa(int n)
{
	char		*res;
	int			len;
	int			is_min;
	long long	num;

	num = n;
	is_min = 0;
	if (num < 0)
		is_min = 1;
	if (is_min)
		len = ft_itoa_len(-num) + 1;
	else
		len = ft_itoa_len(num);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = '\0';
	ft_do_itoa(res, &num, &len, &is_min);
	return (res);
}

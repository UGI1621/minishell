/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:37:37 by saan              #+#    #+#             */
/*   Updated: 2024/10/22 17:29:32 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_cal_div(long long n)
{
	long long	div;

	div = 1;
	while (n >= 10)
	{
		n /= 10;
		div *= 10;
	}
	return (div);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	long long	div;
	char		temp;

	num = (long long)n;
	if (num < 0)
	{
		num = -num;
		write(fd, "-", 1);
	}
	else if (num == 0)
	{
		temp = '0';
		write(fd, &temp, 1);
		return ;
	}
	div = ft_cal_div(num);
	while (div > 0)
	{
		temp = (num / div) + '0';
		write(fd, &temp, 1);
		num %= div;
		div /= 10;
	}
}

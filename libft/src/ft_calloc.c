/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:59:35 by saan              #+#    #+#             */
/*   Updated: 2024/10/29 19:48:30 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*temp;

	if (size && (number > SIZE_MAX / size))
		return (NULL);
	temp = (void *)malloc(number * size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, number * size);
	return (temp);
}

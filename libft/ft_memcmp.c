/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:28:23 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/21 23:28:59 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	diff;
	int	i;

	i = -1;
	diff = 0;
	while (++i < (int)n && diff == 0)
		diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (diff);
}

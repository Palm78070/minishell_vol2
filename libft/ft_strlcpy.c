/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:36:55 by rthammat          #+#    #+#             */
/*   Updated: 2022/03/01 13:12:45 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = -1;
	while (src[++len] && dstsize && len < dstsize - 1)
		dst[len] = src[len];
	if (len < dstsize)
		dst[len] = 0;
	while (src[len])
		++len;
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:43:27 by rthammat          #+#    #+#             */
/*   Updated: 2022/03/01 13:13:52 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	s_len;

	len = 0;
	s_len = -1;
	while (dst[len] && len < dstsize)
		++len;
	while (src[++s_len] && dstsize && len + s_len < dstsize - 1)
		dst[len + s_len] = src[s_len];
	if (s_len)
		dst[len + s_len] = 0;
	while (src[s_len])
		++s_len;
	return (len + s_len);
}

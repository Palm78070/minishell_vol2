/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:33:48 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/21 23:34:00 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hst, const char *nd, size_t len)
{
	size_t	len2;
	char	*res;
	char	*input;
	int		i;

	res = (char *)hst;
	input = (char *)nd;
	len2 = ft_strlen(input);
	i = 0;
	if (ft_strlen(input) == 0)
		return (res);
	while (res[i] && (len > 0))
	{
		if (res[i] == input[0] && len2 <= len)
		{
			if (ft_strncmp(&res[i], &input[0], len2) == 0)
				return (&res[i]);
		}
		++i;
		--len;
	}
	return (NULL);
}

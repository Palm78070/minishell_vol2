/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:50:29 by rthammat          #+#    #+#             */
/*   Updated: 2022/03/01 12:52:10 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s == NULL || !s)
		return (-1);
	while (s[i])
	{
		while (s[i] == c)
			++i;
		if (s[i] != c && s[i])
			++count;
		while (s[i] != c && s[i])
			++i;
	}
	return (count);
}

static int	free_mem(char **s, int indx)
{
	if (!s[indx])
	{
		while (indx > 0)
			free(s[indx--]);
		free(s);
		return (1);
	}
	return (0);
}

static char	*input_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = 0;
	while (s[i] && s[i] != c)
		++i;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		str_len;
	char	**result;

	i = -1;
	result = NULL;
	str_len = count_words(s, c);
	if (str_len == -1)
		return (NULL);
	result = (char **)malloc((str_len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (++i < str_len)
	{
		while (s[0] == c)
			++s;
		result[i] = input_str(s, c);
		if (free_mem(result, i))
			return (NULL);
		s += ft_strlen(result[i]);
	}
	result[i] = 0;
	return (result);
}

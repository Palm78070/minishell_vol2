/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:22:03 by psutanth          #+#    #+#             */
/*   Updated: 2023/02/23 14:03:09 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_value(char *key, char **envp)
{
	size_t	keylen;

	keylen = ft_strlen(key);
	while (*envp)
	{
		if (ft_strncmp(key, *envp, keylen) == 0
			&& (*envp)[keylen] == '=')
			return (ft_strchr(*envp, '=') + 1);
		++envp;
	}
	return (NULL);
}

void	splice_char_array(char ***arr, size_t index)
{
	size_t	size;
	size_t	i;
	char	**newarr;

	size = 0;
	while ((*arr)[size] != NULL)
		++size;
	newarr = malloc(sizeof(*newarr) * (size + 1));
	if (newarr == NULL)
		return ;
	i = 0;
	while (i < index)
	{
		newarr[i] = (*arr)[i];
		++i;
	}
	free((*arr)[i++]);
	while ((*arr)[i - 1] != NULL)
	{
		newarr[i - 1] = (*arr)[i];
		++i;
	}
	free(*arr);
	*arr = newarr;
}

char	*ft_strjoin_arr(char **arr)
{
	size_t	i;
	char	*newstr;
	char	*temp;

	i = 0;
	newstr = NULL;
	while (arr[i] != NULL)
	{
		temp = ft_strjoin(newstr, arr[i++]);
		if (temp == NULL)
			continue ;
		free(newstr);
		newstr = temp;
	}
	return (newstr);
}

void	free_strarr(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

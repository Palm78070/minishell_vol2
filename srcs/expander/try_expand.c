/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:38:10 by psutanth          #+#    #+#             */
/*   Updated: 2023/02/27 17:45:13 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*simple_expand(char *str, char **envp)
{
	char	*expanded;

	if (str[0] == '$')
	{
		expanded = get_envp_value(str + 1, envp);
		if (expanded != NULL)
		{
			printf("Variable %s expanded to: <%s>\n", str, expanded);
			return (expanded);
		}
		else
		{
			printf("Variable %s not found, substituting empty string\n", str);
			return ("");
		}
	}
	return ("");
}

char	*try_expand_var(char *arg, char **envp)
{
	char	**split;
	char	*expanded;
	char	*newstr;
	size_t	i;

	if (count_var_splits(arg) == 0)
		return (NULL);
	split = make_var_splits(arg);
	i = -1;
	while (split[++i] != NULL)
	{
		if (split[i][0] == '$')
		{
			expanded = ft_strdup(simple_expand(split[i], envp));
			if (expanded != NULL)
			{
				free(split[i]);
				split[i] = expanded;
			}
		}
	}
	newstr = ft_strjoin_arr(split);
	free_strarr(split);
	return (newstr);
}

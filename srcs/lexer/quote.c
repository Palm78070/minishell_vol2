#include "minishell.h"

void	check_quote(char *line, int *indx)
{
	int	i;
	char	quote;

	quote = 0;
	i = *indx;
	if (line[i] && (line[i] == '\'' || line[i] == '"'))
	{
		quote = line[i];
		while (line[++i] && line[i] != quote)
			continue ;
	}
	*indx = i;
}

char	*ft_insert_char(char *old, char c)
{
	char	*res;
	int	len;
	int	i;

	i = 0;
	if (old == NULL)
		len = 2;
	else
		len = ft_strlen(old) + 2;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (old && old[i])
	{
		res[i] = old[i];
		++i;
	}
	res[i++] = c;
	res[i] = '\0';
	if (old)
		free(old);
	return (res);
}

char	*include_quote(char *res, char *old, int *indx)
{
	res = ft_insert_char(res, old[*indx]);
	*indx += 1;
	while (old[*indx] && old[*indx] != '\'')
	{
		res = ft_insert_char(res, old[*indx]);
		*indx += 1;
	}
	if (old[*indx] && old[*indx] == '\'')
		res = ft_insert_char(res, old[*indx]);
	*indx += 1;
	return (res);
}

char	*remove_quote(char *old)
{
	char	*res;
	char	quote;
	int	i;

	res = NULL;
	i = 0;
	quote = 0;
	while (old && old[i])
	{
		if (old[i] == '\'' || old[i] == '"')
		{
			quote = old[i];
			if (old[i + 1] && old[i] == '\'' && old[i + 1] == '$')
				res = include_quote(res, old, &i);
			if (old[i] && (old[i] == '\'' || old[i] == '"'))
				++i;
			while (old[i] && old[i] != quote)
				res = ft_insert_char(res, old[i++]);
			if (old[i])
				++i;
		}
		else
			res = ft_insert_char(res, old[i++]);
	}
	if (old)
		free(old);
	return (res);
}

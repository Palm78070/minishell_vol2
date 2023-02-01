#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	check_quote(char *line, int *indx)
{
	int	i;
	char	quote;

	quote = 0;
	i = *indx;
	//if (line[i] && (line[i] == '\'' || line[i] == '"'))
	if (line[i] && is_quote(line[i]))
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

char	*check_include_quote(char *res, char *old, int *indx)
{
	int	dollar;
	int	i;

	dollar = 0;
	i = *indx;
	//if (!(old[*indx + 1] && is_quote(old[*indx]) && old[*indx + 1] == '$'))
	//	return (res);
	while (old[i] && old[i] != '$')
		++i;
	if (old[i] == '\0')
		return (res);
	res = ft_insert_char(res, old[*indx]);
	*indx += 1;
	//while (old[*indx] && old[*indx] != '\'')
	while (old[*indx] && !is_quote(old[*indx]))
	{
		res = ft_insert_char(res, old[*indx]);
		*indx += 1;
	}
	//if (old[*indx] && old[*indx] == '\'')
	if (old[*indx] && is_quote(old[*indx]))
		res = ft_insert_char(res, old[*indx]);
	if (old[*indx] && old[(*indx) + 1])
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
		//if (old[i] == '\'' || old[i] == '"')
		if (is_quote(old[i]))
		{
			quote = old[i];
			res = check_include_quote(res, old, &i);
			//if (old[i] && (old[i] == '\'' || old[i] == '"'))
			if (old[i] && is_quote(old[i]))
				++i;
			while (old[i] && old[i] != quote)
				res = ft_insert_char(res, old[i++]);
			if (old[i])
				++i;
		}
		else
			res = ft_insert_char(res, old[i++]);
	}
	free(old);
	return (res);
}

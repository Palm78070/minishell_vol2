#include "minishell.h"

int	is_arrow(char c)
{
	return (c == '<' || c == '>');
}

int	is_not_file(char *s, int i)
{
	if (s[i + 1] && s[i] == '>' && s[i + 1] == '>')
	{
		i += 2;
		while (s[i] && ft_isspace(s[i]))
			++i;
		if (is_blank_quote(&s[i]))
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	else if (s[i] == '<' || s[i] == '>')
	{
		++i;
		while (s[i] && ft_isspace(s[i]))
			++i;
		if (is_blank_quote(&s[i]))
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	return (0);
}

int	check_error_ok(char *s)
{
	char	c;
	int	flag;
	int	i;

	c = 0;
	i = 0;
	if (!quote_error_ok(s, &c))
		return (0);
	flag = arrow_error_ok(s, &c, &i);
	if (flag == -1)
	{
		flag = 0;
		printf("syntax error near unexpected token '");
		while (s[i] && s[i] == c && flag++ != 3)
			printf("%c", s[i++]);
		printf("'\n");
		return (0);
	}
	else if (flag == 0)
		printf("syntax error near unexpected token 'newline'\n");
	if (!pipe_error_ok(s, 1) || flag <= 0)
		return (0);
	return (1);
}

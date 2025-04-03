/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:53:43 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/10 18:18:06 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

int	ft_check_redir(char **args, int i)
{
	char	*temp;
	int		j;

	j = 0;
	if (ft_redir_type(args[i]) == parse_error)
	{
		printf("%s: parse error near `>'\n", MINISHELL_NAME);
		return (-1);
	}
	temp = ft_strchr(args[i], ft_operator_redir(ft_redir_type(args[i])));
	while (temp && ft_redir_type(temp + j) != none)
	{
		j = 0;
		while (temp[j] && (temp[j] == 32 || is_dif_operator(temp[j])))
			j++;
		if ((ft_redir_type(args[i]) != none && !temp[j])
			|| is_dif_operator(temp[ft_strlen(temp) - 1]))
		{
			printf("%s: syntax error near unexpected token `>'\n",
				MINISHELL_NAME);
			return (-1);
		}
		temp = ft_strchr(temp + j, ft_operator_redir(ft_redir_type(temp + j)));
	}
	return (0);
}

int	ft_check_pipe(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = ft_next_quote(str[i], str, i + 1);
		if ((str[i] == '|' && str[i + 1] == '|')
			|| (str[i] == '|' && str[i + 1] == '\0')
			|| str[0] == '|')
		{
			printf("syntax error near unexpected token '|'\n");
			return (-1);
		}
		if (str[i] == '|')
			num++;
	}
	return (num);
}

static int	ft_quote_pair(char *str, int *i, char c)
{
	int	n;

	n = 1;
	while (str[(*i) + 1] && str[(*i) + 1] != c)
		(*i)++;
	if (str[(*i) + 1] == c)
		n++;
	(*i)++;
	return (n);
}

static int	ft_check_dquote(char *input, t_mini *mini)
{
	int	i;
	int	simple;
	int	doble;

	i = -1;
	simple = 2;
	doble = 2;
	while (input[++i])
	{
		if (input[i] == 39)
			simple += ft_quote_pair(input, &i, input[i]);
		if (input[i] == 34)
			doble += ft_quote_pair(input, &i, input[i]);
		if (simple % 2 != 0 || doble % 2 != 0)
		{
			mini->flags->quote = 1;
			printf("dquote>\n");
			return (0);
		}
	}
	return (1);
}

int	ft_token_types(t_mini **mini, char *input, char ***tokens)
{
	(*mini)->flags->quote = ft_check_dquote(input, (*mini));
	if ((*mini)->flags->quote == 0)
		return (1);
	(*mini)->flags->pipe = ft_check_pipe(input);
	if ((*mini)->flags->pipe == -1)
		return (1);
	*tokens = ft_split_pipes(input);
	if ((*tokens) == NULL)
		return (1);
	return (0);
}

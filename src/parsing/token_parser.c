/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:39:56 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 16:12:39 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"
#include <utils.h>

static int	ft_split_args(t_handle_argument *a)
{
	a->start = 0;
	while (a->str[++(a->i)])
	{
		handle_space_and_start(a->str, &(a->i), &(a->start));
		a->i = handle_quotes(a->str, &(a->i));
		if (!ft_isspace(a->str[a->i]) && !ft_isdifoperator(a->str[a->i])
			&& (a->str[a->i + 1] == ' ' || a->str[a->i + 1] == '\0'
				|| ft_isdifoperator(a->str[a->i + 1])))
		{
			handle_argument(a);
			if (ft_isdifoperator(a->str[a->i + 1]))
				a->start = a->i + 1;
		}
		else if (ft_isdifoperator(a->str[a->i]) && a->str[a->i + 1]
			&& !ft_isdifoperator(a->str[a->i + 1]))
		{
			handle_argument(a);
			a->start = a->i + 1;
		}
	}
	a->args[a->j] = NULL;
	return (a->i);
}

static char	**ft_get_args(t_mini *mini, char *str, t_cmd *cmd)
{
	t_handle_argument	argument;

	argument.args = malloc(sizeof(char *) * (cmd->num_args + 1));
	argument.str = str;
	argument.i = -1;
	argument.j = 0;
	if (!argument.args)
		ft_exit_error("Malloc", 2);
	mini->total_chars += ft_split_args(&argument);
	return (argument.args);
}

static char	*ft_get_cmd(char *input, t_mini *mini)
{
	int		i;
	int		start;
	char	*str;
	char	*tmp_cmd;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	start = i;
	while (input[i] && !ft_isspace(input[i]) && !is_dif_operator(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_next_quote(input[i], input, i + 1);
		i++;
	}
	tmp_cmd = ft_substr(input, start, i - start);
	str = ft_str_noquotes(tmp_cmd);
	free(tmp_cmd);
	mini->total_chars += i;
	return (str);
}

t_cmd	*ft_create_cmd(t_mini *mini, char *input)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		ft_exit_error("Malloc", 2);
	cmd->cmd = ft_get_cmd(input, mini + mini->total_chars);
	cmd->num_args = ft_num_args(input + mini->total_chars);
	cmd->next = NULL;
	cmd->flags = mini->flags;
	cmd->env = mini->env;
	if (cmd->num_args == 0)
		return (cmd);
	cmd->args = ft_get_args(mini, input + mini->total_chars, cmd);
	return (cmd);
}

int	ft_token_parser(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**tokens;
	t_cmd	*temp;
	int		i;

	i = 0;
	tokens = NULL;
	mini->total_chars = 0;
	if (ft_token_types(&mini, input, &tokens))
		return (0);
	*cmd = ft_create_cmd(mini, tokens[0]);
	if (ft_check_dolar(input))
		ft_expand(cmd);
	while (++i <= mini->flags->pipe)
	{
		mini->total_chars = 0;
		temp = ft_create_cmd(mini, tokens[i]);
		if (ft_check_dolar(input))
			ft_expand(&temp);
		ft_last_cmd(*cmd, temp);
		temp = temp->next;
	}
	while (i--)
		free(tokens[i]);
	free(tokens);
	return (1);
}

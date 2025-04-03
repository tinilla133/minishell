/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:48:54 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 13:33:19 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

int	ft_num_args(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if ((str[i] != 32 && str[i] != 34 && str[i] != 39
				&& !ft_isdifoperator(str[i])) && (str[i + 1] == 32
				|| str[i + 1] == '\0' || str[i + 1] == 34
				|| str[i + 1] == 39 || ft_isdifoperator(str[i + 1])))
			num++;
		else if (ft_isdifoperator(str[i]) && str[i + 1]
			&& !ft_isdifoperator(str[i + 1]))
			num++;
		if (str[i] == 34 || str[i] == 39)
		{
			i = ft_next_quote(str[i], str, i + 1);
			num++;
		}
	}
	return (num);
}

char	**ft_split_pipes(char *str)
{
	char	**lines;
	int		i;

	i = -1;
	lines = ft_calloc(sizeof(char *), (ft_check_pipe(str) + 2));
	if (!lines)
		ft_exit_error("Malloc", 2);
	ft_fill_lines(str, lines, -1, 0);
	while (lines[++i])
	{
		if (ft_check_pipe(lines[i]) == -1 || ft_check_redir(lines, i) == -1)
		{
			g_exit = 2;
			while (i >= 0)
				free(lines[i--]);
			free(lines);
			return (NULL);
		}
	}
	return (lines);
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	ft_clear_lst(t_cmd **cmd)
{
	t_cmd	*temp;
	t_cmd	*temp2;
	int		i;

	temp = *cmd;
	while (cmd && temp)
	{
		i = -1;
		temp2 = temp->next;
		free(temp->cmd);
		while (temp->args && temp->args[++i])
			free(temp->args[i]);
		free(temp->args);
		free(temp);
		temp = temp2;
	}
}

int	ft_isdifoperator(char c)
{
	return (c == '>' || c == '<');
}

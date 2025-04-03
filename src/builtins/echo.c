/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:00:26 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 12:57:58 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_char_with_quotes(char c, int *quote)
{
	if ((c == '"' || c == '\''))
	{
		if (*quote && c != *quote)
			printf("%c", c);
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
	else
		printf("%c", c);
}

static void	ft_print_args(char **cmd, int start)
{
	int	i;
	int	j;
	int	quote;

	i = start;
	while (cmd[i])
	{
		j = -1;
		quote = 0;
		while (cmd[i][++j])
			print_char_with_quotes(cmd[i][j], &quote);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

static int	ft_echo_nl(char *str)
{
	int	i;

	if (!str || ft_strncmp(str, "-n", 2))
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = -1;
	new_line = 1;
	if (!args)
	{
		printf("\n");
		return (0);
	}
	while (args[++i] && ft_echo_nl(args[i]))
		new_line = 0;
	ft_print_args(args, i);
	if (new_line)
		printf("\n");
	return (0);
}

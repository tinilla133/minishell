/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:58:23 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 19:32:10 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <builtins.h>
#include <utils.h>

void	handle_space_and_start(char *str, int *i, int *start)
{
	if (ft_isspace(str[*i]) && str[*i + 1] && str[*i + 1] != ' ')
		*start = *i + 1;
}

int	handle_quotes(char *str, int *i)
{
	if (str[*i] == 34 || str[*i] == 39)
		*i = ft_next_quote(str[*i], str, *i + 1);
	return (*i);
}

void	handle_argument(t_handle_argument *arguments)
{
	if (arguments->start <= arguments->i)
	{
		arguments->args[arguments->j] = ft_substr(arguments->str, \
					arguments->start, arguments->i - arguments->start + 1);
		if (!arguments->args[arguments->j])
			ft_exit_error("Malloc", 2);
		(arguments->j)++;
	}
}

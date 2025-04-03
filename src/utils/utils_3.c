/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:43:46 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 13:49:30 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

int	process_redirection(char *arg, int *i, t_rtype type)
{
	if (ft_redir_type(arg + *i) == type)
	{
		if (type == dgreat || type == dless)
			(*i)++;
		(*i)++;
	}
	return (*i);
}

int	ft_next_quote(char c, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_str_isspace(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			j++;
	}
	if (i == j)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

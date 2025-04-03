/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:12:02 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/10 18:18:44 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

char	ft_operator_redir(t_rtype type)
{
	if (type == great || type == dgreat)
		return ('>');
	else
		return ('<');
}

inline int	is_dif_operator(char c)
{
	return (c == '<' || c == '>');
}

inline int	get_next_redir(int i, char *str)
{
	while (str[i] && !is_dif_operator(str[i]))
		i++;
	return (i);
}

t_rtype	ft_redir_type(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = ft_next_quote(str[i], str, i +1);
		if (str[i] == '>' && !is_dif_operator(str[i + 1]))
			return (great);
		if (str[i] == '>' && str[i + 1] == '>' && !is_dif_operator(str[i + 2]))
			return (dgreat);
		if (str[i] == '<' && !is_dif_operator(str[i + 1]))
			return (less);
		if (str[i] == '<' && str[i + 1] == '<' && !is_dif_operator(str[i + 2]))
			return (dless);
		if (is_dif_operator(str[i]))
			return (parse_error);
	}
	return (none);
}

int	is_redir(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_redir_type(args[i]) != none)
			return (i);
		i++;
	}
	return (-1);
}

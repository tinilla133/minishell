/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:28:06 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/11 18:35:36 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int str_to_free)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (str_to_free == 1)
		free(s1);
	else if (str_to_free == 2)
		free (s2);
	else if (str_to_free == 3)
	{
		free (s1);
		free (s2);
	}
	return (new_str);
}

char	*str_nospaces(char *str)
{
	int		i;
	int		j;
	char	*cmd;

	i = -1;
	j = 0;
	cmd = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[++i])
	{
		if (str[i] != 32)
			cmd[j++] = str[i];
	}
	cmd[j] = '\0';
	return (cmd);
}

int	ft_check_dolar_digit(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1]
			&& ((ft_isalnum(input[i + 1]))
				|| (input[i + 1] == '*' || input[i + 1] == '@'
					|| input[i + 1] == 92)))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_special(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				return (1);
		}
	}
	return (0);
}

int	ft_check_dolar(char *input)
{
	int	i;
	int	doble;

	i = 0;
	doble = 1;
	while (input[i])
	{
		if (input[i] == 39 && doble == 1)
			i = ft_next_quote(input[i], input, i + 1);
		if (input[i] == 34)
			doble *= -1;
		if (input[i] == '$' && (input[i + 1] && input[i + 1] != ' '))
			return (1);
		i++;
	}
	return (0);
}

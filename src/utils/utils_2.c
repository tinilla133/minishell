/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:25:14 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 19:16:59 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_error(char *str, int n)
{
	if (n)
		perror("Error");
	printf("%s\n", str);
	exit(n);
}

char	*ft_str_noquotes(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = -1;
	j = -1;
	doubles = 1;
	simples = 1;
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		ft_exit_error("Error malloc", 11);
	while (str[++i])
	{
		if (str[i] == 34 && simples != -1)
			doubles = -doubles;
		else if (str[i] == 39 && doubles != -1)
			simples = -simples;
		else
			temp[++j] = str[i];
	}
	return (temp);
}

void	ft_last_cmd(t_cmd *c1, t_cmd *c2)
{
	while (c1->next)
		c1 = c1->next;
	c1->next = c2;
}

int	ft_count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	ft_fill_lines(char *str, char **lines, int i, int j)
{
	int	start;

	start = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = ft_next_quote(str[i], str, i + 1);
		if (str[i] != '|' && (str[i + 1] == '|' || str[i + 1] == '\0'))
		{
			lines[j] = ft_substr(str, start, (i - start) + 1);
			if (lines[j] == NULL)
			{
				while (j-- > 0)
					free(lines[j]);
				free(lines);
				ft_exit_error("Malloc", 1);
			}
			j++;
		}
		if (str[i] == '|' && (str[i + 1] != '|' || str[i + 1] != '\0'))
			start = i + 1;
	}
	lines[j] = NULL;
}

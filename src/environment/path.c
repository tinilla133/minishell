/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:40:20 by franciscovl       #+#    #+#             */
/*   Updated: 2024/10/08 17:28:13 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/environment.h"

char	**ft_parse_path(char **env)
{
	char	**path;
	char	*buffer;

	buffer = ft_get_env_var_mshell("PATH", env);
	if (!buffer)
		return (NULL);
	path = ft_split(buffer, ':');
	free(buffer);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_check_absolute(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

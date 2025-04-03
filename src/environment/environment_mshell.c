/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_mshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya42 <fvizcaya42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:51 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/04 21:13:47 by fvizcaya42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*ft_strstr_env_var_mshell(const char *var_name, char **env)
{
	size_t	len;

	len = ft_strlen(var_name);
	while (*env)
	{
		if (!ft_strncmp(*env, var_name, len) && *env[len] == '=')
			return (*env);
		env++;
	}
	return (NULL);
}

int	ft_position_env_var_mshell(const char *var_name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && (env[i][len] == '=' || \
			(long unsigned) ft_strlen(env[i]) == len))
			return (i);
		i++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:31:47 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/11/19 19:33:39 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_get_env_size(char **envp)
{
	size_t	count;

	if (!envp)
		return (0);
	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**ft_getenv(char **envp, size_t *env_size)
{
	size_t		nvars;
	size_t		i;
	char		**env;

	nvars = ft_get_env_size(envp);
	env = (char **) malloc((nvars + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i > 0)
				free(env[--i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	if (env_size)
		*env_size = nvars;
	return (env);
}

char	*ft_get_env_var_mshell(const char *var_name, char **env)
{
	size_t	i;
	size_t	env_size;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	if (ft_strncmp(var_name, "\"$\"", 4) == 0)
		return ("$");
	env_size = ft_get_env_size(env);
	while (i < env_size)
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

size_t	ft_get_size_env_mshell(const char **env)
{
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

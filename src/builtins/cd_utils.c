/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:09:15 by fvizcaya42        #+#    #+#             */
/*   Updated: 2024/12/14 19:28:11 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <cd_functions.h>

static char	**ft_realloc_env_mshell(t_cmd *cmd);

int	ft_export_pwd(const char *path, t_cmd *cmd)
{
	char	*buffer_aux;

	cmd->env->env = ft_realloc_env_mshell(cmd);
	buffer_aux = ft_strdup("PWD=");
	cmd->env->env[cmd->env->num_env - 1] = ft_strjoin(buffer_aux, path);
	free(buffer_aux);
	return (0);
}

int	ft_update_pwd(const char *path, t_cmd *cmd)
{
	int		position;
	char	*buffer;
	char	*buffer_aux;

	position = ft_position_env_var_mshell("PWD", cmd->env->env);
	if (position == -1)
		ft_export_pwd(path, cmd);
	else
	{
		buffer = ft_realloc(cmd->env->env[position], \
					ft_strlen(path) + ft_strlen("PWD=") + 1);
		ft_strlcpy(buffer, "PWD=", ft_strlen("PWD=") + 1);
		buffer_aux = ft_strjoin(buffer, path);
		free (buffer);
		cmd->env->env[position] = buffer_aux;
	}
	return (0);
}

int	ft_export_oldpwd(const char *path, t_cmd *cmd)
{
	char	*buffer_aux;

	cmd->env->env = ft_realloc_env_mshell(cmd);
	buffer_aux = ft_strdup("OLDPWD=");
	cmd->env->env[cmd->env->num_env - 1] = ft_strjoin(buffer_aux, path);
	free(buffer_aux);
	return (0);
}

int	ft_update_oldpwd(const char *path, t_cmd *cmd)
{
	int		position;
	char	*buffer;

	position = ft_position_env_var_mshell("OLDPWD", cmd->env->env);
	if (position == -1)
		ft_export_oldpwd(path, cmd);
	else
	{
		buffer = ft_realloc(cmd->env->env[position], \
					ft_strlen(path) + ft_strlen("OLDPWD=") + 1);
		ft_strlcpy(buffer, "OLDPWD=", ft_strlen("OLDPWD=") + 1);
		cmd->env->env[position] = ft_strjoin(buffer, path);
		free (buffer);
	}
	return (0);
}

static char	**ft_realloc_env_mshell(t_cmd *cmd)
{
	size_t		i;
	char		**new_env;

	new_env = (char **) malloc ((cmd->env->num_env + 2) * sizeof (char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < cmd->env->num_env)
	{
		new_env[i] = ft_strdup(cmd->env->env[i]);
		i++;
	}
	new_env[(cmd->env->num_env) + 1] = NULL;
	ft_free_two_dim_array(cmd->env->env);
	(cmd->env->num_env)++;
	return (new_env);
}

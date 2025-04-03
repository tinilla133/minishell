/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:16:40 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 19:27:21 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include <utils.h>

char	**ft_grow_env_mshell(t_cmd *cmd)
{
	size_t		i;
	size_t		size;
	char		**new_env;

	size = cmd->env->num_env;
	new_env = (char **) malloc ((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(cmd->env->env[i]);
		i++;
	}
	new_env[(size) + 1] = NULL;
	ft_free_two_dim_array(cmd->env->env);
	cmd->env->num_env++;
	return (new_env);
}

int	ft_char_position_str(const char *str, char c)
{
	int	position;

	position = 0;
	while (str[position])
	{
		if (str[position] == c)
			return (position);
		position++;
	}
	return (-1);
}

int	ft_is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void	ft_do_export(char *var_name, t_cmd *cmd, int i)
{
	int	var_position;

	var_position = ft_position_env_var_mshell(var_name, cmd->env->env);
	if (var_position == -1)
	{
		cmd->env->env = ft_grow_env_mshell(cmd);
		cmd->env->env[(cmd->env->num_env) - 1] = ft_strdup(cmd->args[i]);
	}
	else
	{
		free(cmd->env->env[var_position]);
		cmd->env->env[var_position] = ft_strdup(cmd->args[i]);
	}
}

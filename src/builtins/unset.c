/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:12:45 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/14 19:27:41 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include <utils.h>

static char	**ft_short_env_mshell(t_cmd *cmd, size_t to_remove)
{
	size_t		i;
	size_t		j;
	char		**new_env;

	new_env = (char **)malloc(cmd->env->num_env * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < cmd->env->num_env)
	{
		if (i != to_remove)
			new_env[j++] = ft_strdup(cmd->env->env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_two_dim_array(cmd->env->env);
	cmd->env->num_env--;
	return (new_env);
}

int	ft_unset(t_cmd *cmd)
{
	size_t	i;
	int		var_position;

	i = -1;
	if (!cmd->args)
		return (0);
	while (cmd->args[++i])
	{
		var_position = ft_position_env_var_mshell(cmd->args[i], cmd->env->env);
		if (var_position == -1)
			return (0);
		else
			cmd->env->env = ft_short_env_mshell(cmd, (size_t) var_position);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:20:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/10 17:16:31 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "environment.h"
#include <utils.h>

static int	ft_print_env_export(char **env)
{
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int		eq_position;
	char	*var_name;
	size_t	i;

	i = -1;
	var_name = NULL;
	if (((!cmd->args) || !cmd->args[0]) || (cmd->num_args == 1 && \
		!ft_strncmp(*cmd->args, "-p", 2) && ft_strlen(*cmd->args) == 2))
		return (ft_print_env_export(cmd->env->env));
	if (cmd->num_args > 1 && !ft_strncmp(*cmd->args, "-p", 2) && \
		ft_strlen(*cmd->args) == 2)
		cmd->args++;
	while (cmd->args[++i])
	{
		if (!ft_is_valid_identifier(cmd->args[i]))
			return (printf("export: `%s`: not a valid identifier\n", \
						cmd->args[i]), 1);
		eq_position = ft_char_position_str(cmd->args[i], '=');
		if (eq_position == -1)
			var_name = ft_strdup(cmd->args[i]);
		else
			var_name = ft_substr(cmd->args[i], 0, eq_position);
		(ft_do_export(var_name, cmd, i), free (var_name));
	}
	return (0);
}

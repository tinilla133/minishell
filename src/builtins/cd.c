/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:26:34 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/11 21:13:49 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include <cd_functions.h>

static char	*ft_set_destination_oldpwd(t_cmd *cmd)
{
	char	*destination;

	if (ft_strlen(cmd->args[0]) == 1)
	{
		destination = ft_get_env_var_mshell("OLDPWD", cmd->env->env);
		if (!destination)
			printf ("%s: cd: OLDPWD not set	\n", MINISHELL_NAME);
	}
	else
	{
		printf("%s: cd: %c%c: invalid option\n", MINISHELL_NAME, \
						cmd->args[0][0], cmd->args[0][1]);
		return (NULL);
	}
	return (destination);
}

static char	*ft_set_destination(t_cmd *cmd, int i)
{
	char	*destination;
	char	*aux_ptr;

	if (cmd->args[i][0] == '~')
	{
		if (ft_strlen(cmd->args[i]) == 1)
			destination = ft_get_env_var_mshell("HOME", cmd->env->env);
		else
		{
			aux_ptr = ft_get_env_var_mshell("HOME", cmd->env->env);
			destination = ft_strjoin_free(aux_ptr, ft_substr(cmd->args[i], 1, \
									ft_strlen(cmd->args[i])), 3);
		}
	}
	else if (cmd->args[i][0] == '-')
		destination = ft_set_destination_oldpwd(cmd);
	else
		destination = cmd->args[i];
	return (destination);
}

static int	ft_do_change_dir(t_cmd *cmd, int i)
{
	char	buffer[CWD_MAX_SIZE];
	char	oldpwd[CWD_MAX_SIZE];
	char	*destination;

	destination = ft_set_destination(cmd, i);
	if (!destination)
		return (1);
	getcwd(oldpwd, CWD_MAX_SIZE);
	if (chdir(destination))
	{
		printf("%s: cd: %s: No such file or directory\n", \
				MINISHELL_NAME, cmd->args[0]);
		return (1);
	}
	if (ft_position_env_var_mshell("PWD", cmd->env->env) == -1)
		ft_update_oldpwd("", cmd);
	else
		ft_update_oldpwd(oldpwd, cmd);
	ft_update_pwd(getcwd(buffer, CWD_MAX_SIZE), cmd);
	if (cmd->args[0][0] == '~' || cmd->args[0][0] == '-')
		free (destination);
	return (0);
}

int	ft_change_dir(t_cmd *cmd)
{
	int	i;

	if (cmd->num_args > 1)
		return (ft_args_num("cd"), 1);
	if (cmd->num_args == 0)
	{
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		cmd->args = (char **) malloc(2 * sizeof(char *));
		if (!cmd->args)
			return (-1);
		cmd->args[0] = ft_strdup("~");
		cmd->args[1] = NULL;
	}
	i = 0;
	while (cmd->args[i] && !cmd->args[i][0])
		i++;
	return (ft_do_change_dir(cmd, i));
}

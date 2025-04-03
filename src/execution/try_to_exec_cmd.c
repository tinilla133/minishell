/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_exec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:54:42 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 19:26:32 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "builtins.h"
#include "utils.h"
#include <errno.h>

char	*find_command_path(char *cmd, char **env, int i)
{
	char	**paths;
	char	*full_path;
	char	*parse_cmd;

	paths = ft_parse_path(env);
	if (!paths)
		return (NULL);
	parse_cmd = ft_strjoin("/", cmd);
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], parse_cmd);
		if (!access(full_path, X_OK))
		{
			free(parse_cmd);
			return (free_paths_and_return(paths, full_path));
		}
		free(full_path);
	}
	free(parse_cmd);
	return (free_paths_and_return(paths, NULL));
}

char	**arg_with_command(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	if (!cmd->args)
	{
		args = ft_calloc(sizeof(char *), 2);
		if (!args)
			ft_exit_error("Error malloc", 36);
	}
	else
	{
		while (cmd->args[i])
			i++;
		args = ft_calloc(sizeof(char *), i + 2);
		if (!args)
			ft_exit_error("Error malloc", 37);
		while (i > 0)
		{
			args[i] = ft_str_noquotes(cmd->args[i - 1]);
			i--;
		}
	}
	args[0] = cmd->cmd;
	return (args);
}

static int	try_absolute_path(t_cmd *cmd, char **args)
{
	if (access(cmd->cmd, X_OK) != -1)
	{
		if (execve(cmd->cmd, args, cmd->env->env) == -1)
		{
			perror("Error");
			g_exit = errno;
		}
	}
	else
	{
		ft_print_and_set_error(cmd->cmd);
		ft_free_two_dim_array(args);
		return (g_exit);
	}
	return (0);
}

static int	ft_exec_absolute_path(t_cmd *cmd, char **args, char *absolute_path)
{
	if (absolute_path)
	{
		if (execve(absolute_path, args, cmd->env->env) == -1
			&& (!ft_str_isspace(cmd->cmd) || cmd->cmd[0] != '\0'))
		{
			perror("Error: ");
			return (errno);
		}
	}
	else
	{
		g_exit = 127;
		(ft_putstr_fd(MINISHELL_NAME, 2), ft_putstr_fd(": ", 2));
		(ft_putstr_fd(cmd->cmd, 2), ft_putstr_fd(": command not found\n", 2));
		free(absolute_path);
	}
	return (0);
}

int	ft_try_exec_cmd(t_cmd *cmd)
{
	char	*absolute_path;
	char	**args;

	args = arg_with_command(cmd);
	if (!args)
		return (1);
	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
		|| (cmd->cmd[0] == '.' && cmd->cmd[1] == '.' && cmd->cmd[2] == '/'))
		return (try_absolute_path(cmd, args));
	absolute_path = find_command_path(cmd->cmd, cmd->env->env, -1);
	ft_exec_absolute_path(cmd, args, absolute_path);
	return (ft_free_two_dim_array(args), g_exit);
}

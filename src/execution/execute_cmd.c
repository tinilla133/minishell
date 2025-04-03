/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:21 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/13 17:28:00 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "redir.h"

int	ft_cmd_type(t_cmd *cmd, char *tmp_cmd)
{
	if (!ft_strncmp(tmp_cmd, "echo", 5))
		return (ft_echo(cmd->args));
	else if (!ft_strncmp(tmp_cmd, "cd", 3))
		return (ft_change_dir(cmd));
	else if (!ft_strncmp(tmp_cmd, "pwd", 4))
		return (ft_pwd(cmd->env->env));
	else if (!ft_strncmp(tmp_cmd, "env", 4))
		return (ft_env(cmd->env->env));
	else if (!ft_strncmp(tmp_cmd, "export", 7))
		return (ft_export(cmd));
	else if (!ft_strncmp(tmp_cmd, "unset", 6))
		return (ft_unset(cmd));
	else if (!ft_strncmp(tmp_cmd, "exit", 5))
		ft_exit(cmd);
	else
		return (ft_try_exec_cmd(cmd));
	return (1);
}

static void	ft_cmd_process(t_cmd *cmd, char *str)
{
	if (dup2(cmd->pipes->out_error, STDERR_FILENO) == -1)
		ft_exit_error("Error DUP", 1);
	if (dup2(cmd->pipes->in, STDIN_FILENO) == -1)
		ft_exit_error("Error DUP", 1);
	if (dup2(cmd->pipes->out, STDOUT_FILENO) == -1)
		ft_exit_error("Error DUP", 1);
	if (cmd->pipes->last)
	{
		cmd->pipes->last = 0;
		ft_set_pipes(cmd->pipes, 0);
	}
	if (close(cmd->pipes->in) == -1)
		ft_exit_error("Error Close", 1);
	if (close(cmd->pipes->out) == -1)
		ft_exit_error("Error Close", 1);
	exit(ft_cmd_type(cmd, str));
}

static void	wait_exit(t_pipe *pipes, int i, pid_t pid, t_cmd **cmd)
{
	int	temp_pid;
	int	temp;

	ft_clear_lst(cmd);
	if (close(pipes->in) == -1)
		ft_exit_error("Close", 1);
	if (close(pipes->out) == -1)
		ft_exit_error("Close", 1);
	free(pipes);
	while (--i)
	{
		temp_pid = waitpid(-1, &g_exit, 0);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		if (temp_pid == pid)
			temp = g_exit;
		if (g_exit == 2 || g_exit == 3)
			g_exit = g_exit + 128;
	}
	wait_signal(1);
}

static pid_t	execute_single_cmd(t_cmd **cmd, t_pipe *pipes, int *i)
{
	char	*tmp_cmd;
	pid_t	pid;

	tmp_cmd = ft_str_noquotes((*cmd)->cmd);
	if (!(*cmd)->next)
		pipes->last = 0;
	ft_set_fds(pipes, *i);
	ft_set_pipes(pipes, (*i)++);
	(*cmd)->pipes = pipes;
	if ((*cmd)->args && is_redir((*cmd)->args) != -1)
	{
		if (redir((*cmd)))
		{
			free(tmp_cmd);
			return (-1);
		}
	}
	pid = fork();
	if (pid == -1)
		ft_exit_error("Error fork", 1);
	if (pid == 0)
		ft_cmd_process((*cmd), tmp_cmd);
	(*cmd) = (*cmd)->next;
	free(tmp_cmd);
	return (pid);
}

void	ft_exec_pipe(t_cmd **cmd, t_pipe *pipes, int i)
{
	t_cmd	*temp;
	pid_t	pid;

	temp = *cmd;
	wait_signal(0);
	while ((*cmd))
	{
		pid = execute_single_cmd(cmd, pipes, &i);
		if (pid == -1)
		{
			g_exit = 2;
			return ;
		}
	}
	wait_exit(pipes, i, pid, &temp);
}

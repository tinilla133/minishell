/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:53:12 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/15 13:32:05 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

void	ft_exec_command(t_cmd *cmd)
{
	int	io[2];

	cmd->pipes = ft_init_pipes();
	cmd->pipes->last = 0;
	ft_set_fds(cmd->pipes, 1);
	ft_set_pipes(cmd->pipes, 1);
	if (cmd->args && is_redir(cmd->args) != -1)
		if (redir(cmd))
			return ;
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (dup2(cmd->pipes->out_error, STDERR_FILENO) == -1)
		ft_exit_error("DUP", 1);
	if (dup2(cmd->pipes->in, STDIN_FILENO) == -1)
		ft_exit_error("DUP", 1);
	if (dup2(cmd->pipes->out, STDOUT_FILENO) == -1)
		ft_exit_error("DUP", 1);
	if (close(cmd->pipes->in) == -1)
		ft_exit_error("Close", 1);
	if (close(cmd->pipes->out) == -1)
		ft_exit_error("Close", 1);
	g_exit = ft_cmd_type(cmd, cmd->cmd);
	if (dup2(io[0], STDIN_FILENO) == -1 || dup2(io[1], STDOUT_FILENO) == -1)
		ft_exit_error("DUP", 1);
	free(cmd->pipes);
}

int	ft_check_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->next)
		i = 0;
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		return (1);
	return (i);
}

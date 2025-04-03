/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:04:21 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 13:49:00 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

char	**ft_remove_redir(char **args, int i)
{
	char	**new_args;
	int		j;
	int		k;

	j = 0;
	while (args[j])
		j++;
	new_args = ft_calloc(sizeof(char *), j - 1);
	k = 0;
	j = 0;
	while (args[j])
	{
		if (j != i && j != i + 1)
			new_args[k++] = args[j];
		else
			free(args[j]);
		j++;
	}
	free(args);
	return (new_args);
}

int	ft_apply_redir(t_cmd *cmd, t_rtype type, int i)
{
	int		fd;
	int		sys_call_error;

	sys_call_error = 0;
	if (type == great)
		fd = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == dgreat)
		fd = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == less)
		fd = open(cmd->args[i + 1], O_RDONLY);
	else if (type == dless)
		return (ft_heredoc(cmd, cmd->args[i + 1]));
	else
		return (0);
	if (fd < 0)
		return (-1);
	if (type == great || type == dgreat)
		sys_call_error = dup2(fd, cmd->pipes->out);
	else if (type == less || type == dless)
		sys_call_error = dup2(fd, cmd->pipes->in);
	if (sys_call_error == -1)
		return (perror("Error"), -1);
	close(fd);
	return (0);
}

char	**new_arg(char **args, char *str, int index)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	while (args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	j = 0;
	while (i <= index)
	{
		if (i == index)
			new_args[j] = str;
		else
			new_args[j] = args[i];
		j++;
		i++;
	}
	free(args);
	return (new_args);
}

char	**ft_separe_redir(char **args, int index, t_rtype type)
{
	int		i;
	char	*operator;
	char	*filename;

	while (args[index])
	{
		i = 0;
		i = process_redirection(args[index], &i, type);
		if (!args[index][i])
		{
			if (!args[index + 1])
				return (NULL);
			return (args);
		}
		operator = ft_substr(args[index], 0, i);
		filename = ft_substr(args[index], i, ft_strlen(args[index]) - i);
		args = new_arg(args, operator, index);
		args = new_arg(args, filename, index + 1);
		if (ft_redir_type(args[index + 1]) == none)
			break ;
		index++;
	}
	return (args);
}

int	redir(t_cmd *cmd)
{
	int		redir_index;
	t_rtype	type;

	redir_index = is_redir(cmd->args);
	while (redir_index != -1)
	{
		type = ft_redir_type(cmd->args[redir_index]);
		cmd->args = ft_separe_redir(cmd->args, redir_index, type);
		if (!cmd->args)
			return (1);
		ft_apply_redir(cmd, type, redir_index);
		cmd->args = ft_remove_redir(cmd->args, redir_index);
		redir_index = is_redir(cmd->args);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:55:58 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/03 14:24:53 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "builtins.h"

int	g_exit = 0;

static void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*aux_ptr;

	while (cmd)
	{
		aux_ptr = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->cmd)
			free(cmd->cmd);
		free(cmd);
		cmd = aux_ptr;
	}
}

void	ft_arguments(t_mini *mini)
{
	char	*input;

	while (1)
	{
		input = readline("\e[0;33m" " LoS PollOS HerManOS" "\x1b[0m" " > " );
		if (!input)
			ft_exit_error("exit", 0);
		if (input[0] == '\0' || ft_str_isspace(input) == 1)
			printf("%c", '\0');
		else
		{
			add_history(input);
			if (ft_token_parser(mini, &mini->cmd, input) && \
				mini->flags->quote != 0)
			{
				if (ft_check_builtin(mini->cmd) && mini->flags->pipe == 0)
					ft_exec_command(mini->cmd);
				else
					ft_exec_pipe(&(mini->cmd), ft_init_pipes(), 1);
			}
		}
		if (input[0] != '\0')
			free_cmd(mini->cmd);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	(void)argv;
	mini = NULL;
	if (argc != 1)
		ft_exit_error("Args", 0);
	mini = ft_init(env);
	wait_signal(1);
	ft_arguments(mini);
	return (0);
}

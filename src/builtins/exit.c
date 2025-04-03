/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:25:32 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/10 17:12:41 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_args_num(char *str)
{
	if (!ft_strncmp(str, "exit", 5))
		printf("exit\n");
	printf("%s: %s: too many arguments\n", MINISHELL_NAME, str);
}

void	ft_exit(t_cmd *cmd)
{
	long long	n;
	int			i;

	i = -1;
	n = 0;
	if (cmd->num_args > 0)
	{
		while (cmd->args[0][++i])
		{
			if (ft_isalpha(cmd->args[0][i]))
			{
				printf("exit\n%s: exit: %s: numeric argument required\n",
					MINISHELL_NAME, cmd->args[0]);
				exit (2);
			}
		}
		if (cmd->num_args > 1)
			return (ft_args_num("exit"));
		n = ft_atoi((const char *)cmd->args[0]);
	}
	printf("exit\n");
	if (!cmd->args)
		exit (g_exit);
	exit ((unsigned char)n);
}

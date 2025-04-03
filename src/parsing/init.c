/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:29:35 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 19:30:48 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include <utils.h>

static void	ft_init_env(t_env *env, char **envp)
{
	if (envp)
		env->env = ft_getenv((const char **)envp, &env->num_env);
	if (!env->env)
		ft_exit_error("Malloc env", 3);
	env->path = ft_get_env_var_mshell("PATH", env->env);
	if (!env->path)
	{
		env->path = ft_strdup("/bin:/usr/bin");
		if (!env->path)
			ft_exit_error("Malloc path", 4);
	}
}

t_mini	*ft_init(char **env)
{
	t_mini	*minishell;

	minishell = ft_calloc(sizeof(t_mini), 1);
	if (!minishell)
		ft_exit_error("Malloc", 2);
	minishell->bash_lvl = 2;
	minishell->env = ft_calloc(sizeof(t_env), 1);
	if (!minishell->env)
		ft_exit_error("Malloc", 3);
	ft_init_env(minishell->env, env);
	minishell->flags = ft_calloc(sizeof(t_flags), 1);
	if (!minishell->flags)
		ft_exit_error("Malloc", 4);
	return (minishell);
}

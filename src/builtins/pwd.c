/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:00:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/10 17:15:52 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	ft_pwd(char **env)
{
	char	*pwd;

	pwd = ft_get_env_var_mshell("PWD", env);
	if (!pwd)
		return (-1);
	else
		printf("%s\n", pwd);
	free (pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_and_set_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:45:26 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/14 13:14:05 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_and_set_error(char *cmd)
{
	char	*str_error;

	str_error = ft_strdup(MINISHELL_NAME);
	str_error = ft_strjoin_free(str_error, ": ", 1);
	str_error = ft_strjoin_free(str_error, cmd, 1);
	g_exit = errno;
	perror(str_error);
	free(str_error);
}

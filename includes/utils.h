/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:11 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/14 19:25:30 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_handle_argument
{
	char	*str;
	int		start;
	int		i;
	int		j;
	char	**args;
}				t_handle_argument;

void	*ft_realloc(void *buffer, size_t size);
void	ft_free_two_dim_array(char **ptr);
void	ft_print_and_set_error(char *cmd);
char	*free_paths_and_return(char **paths, char *to_return);
void	handle_space_and_start(char *str, int *i, int *start);
int		handle_quotes(char *str, int *i);
void	handle_argument(t_handle_argument *a);
void	ft_export_default_path(t_env *env);

#endif
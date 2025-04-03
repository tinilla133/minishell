/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:42:00 by franciscovl       #+#    #+#             */
/*   Updated: 2024/12/10 18:45:23 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

/*
 *		Get environment from main's *envp[] and returns it 
 *		as an array of strings.
 */

char	**ft_getenv(const char **envp, size_t *env_size);

/*
 *		Returns an array of char * with each string containing one 
 *		path of PATH environment variable.
 */

char	**ft_parse_path(char **env);

/*
 *  	Returns the value of an environment variable which name is
 *		const char *name. If not found, returns NULL.
 */

char	*ft_get_env_var_mshell(const char *var_name, char **env);

/*
 *  	Compare the value of an str variable which name could be in the 
 		env. If not found, returns NULL.
 */

char	*ft_compare_var_mshell(const char *var_name, char **env);

/*
 *		Returns a pointer to the string containing the environment variable
 *  	which name is const char *var_name. If not found, returns NULL.
 */

char	*ft_strstr_env_var_mshell(const char *var_name, char **env);

/*
 *		Returns the position in environment array of strings 
 *		(parameter char **env) which name is const char *var_name. 
 *		If not found, returns -1.
 */

int		ft_position_env_var_mshell(const char *var_name, char **env);

/*
 *		Returns the number of variables of minishell's environment.
 */

size_t	ft_get_size_env_mshell(const char **env);
int		ft_check_absolute(char *str);

#endif
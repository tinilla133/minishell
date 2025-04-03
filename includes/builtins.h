/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:30:13 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/10 20:44:11 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"

/*
 *		Changes current working directory. Also manipulates environment in the 
 *		way 'cd' builtin does. It behaves as 'cd' builtin.
 */
int		ft_change_dir(t_cmd *cmd);

/*
 *		Returns environmen as char ** after unsetting const char var_name
 *		environmen variable. If variable to unset does not exist, returns NULL
 *		and char **env remains untouched. This behaves as 'unset' builtin.
 *		Note this functions frees char **env.
 *
 */
int		ft_unset(t_cmd *cmd);

/*
 *		It behaves as 'pwd' builtin. Returns -1 if pwd is unset or 
 *		some subfunctions fail.
 */

int		ft_pwd(char **env);

/*
 *		Check the aproppiate number of arguments per function call 
 */
int		ft_args_num(char *str);
int		ft_pwd(char **env);

/*
 *		Behaves as 'env' builtin. Always returns 0.
 */

int		ft_env(char **env);

/*
 *		Behaves as 'export' builtin. @param const char *env_var must contain 
 *		the name and value of exported variabe yet formated. I. e.:
 *		$ export PATH=/usr/local/bin must correspond to this call:
 *		ft_export("PATH=/usr/local/bin", ...). If you execute after: 
 *		$ export PATH=/opt/cross-compiler/tools/bin$PATH, call must be:
 *		ft_export("PATH=/opt/cross-compiler/tools/bin:/usr/local/bin", ...).
 */

int		ft_export(t_cmd *cmd);
char	**ft_grow_env_mshell(t_cmd *cmd);
int		ft_char_position_str(const char *str, char c);
int		ft_is_valid_identifier(const char *str);
void	ft_do_export(char *var_name, t_cmd *cmd, int i);

int		ft_echo(char **cmd);
void	ft_exit(t_cmd *cmd);

int		ft_check_builtin(t_cmd *cmd);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:12:55 by fvizcaya42        #+#    #+#             */
/*   Updated: 2024/12/10 17:18:22 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_FUNCTIONS_H
# define CD_FUNCTIONS_H

# include <minishell.h>

/******************************************************************************
*
*   This functions are auxiliar functions used by cd builtin that needed to be
*   in another file, instead to be static type inside cd file, due to 42 norm
*   restrictions.
*
*******************************************************************************/

/******************************************************************************
 * 
 *  Exports PWD after cd is executed if have been unsed previously.
 * 
 * ****************************************************************************/

int	ft_export_pwd(const char *path, t_cmd *cmd);

/******************************************************************************
 * 
 *  Exports PWD (updates its value) after cd is executed.
 * 
 * ****************************************************************************/

int	ft_update_pwd(const char *path, t_cmd *cmd);

/******************************************************************************
 * 
 *  Exports OLDPWD after cd is executed if have been unsed previously.
 * 
 * ****************************************************************************/

int	ft_export_oldpwd(const char *path, t_cmd *cmd);

/******************************************************************************
 * 
 *  Exports OLDPWD (updates its value) after cd is executed.
 * 
 * ****************************************************************************/

int	ft_update_oldpwd(const char *path, t_cmd *cmd);

#endif
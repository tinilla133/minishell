/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:00:50 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/14 13:49:52 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"

typedef enum e_rtype
{
	none,
	great,
	dgreat,
	less,
	dless,
	parse_error
}	t_rtype;

int		redir(t_cmd *cmd);
int		is_redir(char **args);
int		ft_check_redir(char **args, int i);
int		process_redirection(char *arg, int *i, t_rtype type);
int		get_next_redir(int start, char *str);
int		ft_apply_redir(t_cmd *cmd, t_rtype type, int i);
t_rtype	ft_redir_type(char *str);
int		is_dif_operator(char c);
char	ft_operator_redir(t_rtype type);
int		ft_heredoc(t_cmd *cmd, char *stop);

#endif
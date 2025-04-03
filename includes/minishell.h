/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:56:23 by fmorenil          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:43 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>

# define MINISHELL_NAME "LoS PollOS HerManOS"
# define CWD_MAX_SIZE 4096

# define __DEBUG__

extern int	g_exit;

typedef struct s_env
{
	char	**env;
	char	*path;
	size_t	num_env;
}	t_env;

typedef struct s_pipe
{
	int	fd[2][2];
	int	in;
	int	out;
	int	last;
	int	out_error;
}	t_pipe;

typedef struct s_flags
{
	int	quote;
	int	pipe;
	int	redic;
	int	dollar;
}	t_flags;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				num_args;
	t_env			*env;
	t_pipe			*pipes;
	t_flags			*flags;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	int			bash_lvl;
	int			total_chars;
	t_env		*env;
	t_cmd		*cmd;
	t_flags		*flags;
}				t_mini;

t_mini	*ft_init(char **env);
int		ft_token_parser(t_mini *mini, t_cmd **cmd, char *input);
int		ft_token_types(t_mini **list, char *input, char ***tokens);
int		ft_isspace(char c);
int		ft_str_isspace(char *str);
t_cmd	*ft_create_cmd(t_mini *mini, char *input);
void	ft_exit_error(char *str, int n);
int		ft_check_pipe(char *str);
int		ft_next_quote(char c, char *str, int i);

void	ft_fill_lines(char *str, char **lines, int i, int j);
char	**ft_split_pipes(char *str);
int		ft_isdifoperator(char c);
void	ft_last_cmd(t_cmd *c1, t_cmd *c2);
void	ft_exec_command(t_cmd *cmd);
void	ft_exec_pipe(t_cmd **cmd, t_pipe *pipes, int i);

// EXPAND
void	ft_expand(t_cmd **cmd);
int		ft_check_special(char *str);
int		ft_check_dolar(char *input);
int		ft_check_dolar_digit(char *input);
char	*ft_strjoin_free(char *s1, char *s2, int str_to_free);

char	*ft_str_noquotes(char *str);
char	*str_nospaces(char *str);
void	ft_clear_lst(t_cmd **cmd);
int		ft_cmd_type(t_cmd *cmd, char *tmp_cmd);
int		ft_try_exec_cmd(t_cmd *cmd);
int		ft_num_args(char *str);
void	ft_free_args(char **args);

// PIPES

void	ft_set_pipes(t_pipe *pipes, int i);
void	ft_set_fds(t_pipe *pipe, int i);
t_pipe	*ft_init_pipes(void);

// SIGNALS
void	wait_signal(int i);

#endif
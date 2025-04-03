/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:24 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/13 16:28:16 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

char	*ft_expand_special_var(t_cmd *cmd, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		j;

	if (str[*i + 1] == '?')
	{
		var_value = ft_itoa(g_exit);
		(*i)++;
	}
	else
	{
		j = *i + 1;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'
				|| str[j] == '$' || str[j] == '@' || str[j] == '*'))
			j++;
		if (j <= *i + 1)
			return (NULL);
		var_name = ft_substr(str, *i + 1, j - *i - 1);
		var_value = ft_get_env_var_mshell(var_name, cmd->env->env);
		free(var_name);
		*i = j;
	}
	return (var_value);
}

char	*ft_expand_special(char *str)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				expanded = ft_strjoin_free(expanded, ft_itoa(g_exit), 3);
				i++;
			}
			else if (str[i + 1] == '$')
				expanded = ft_strjoin_free(expanded, ft_strdup("$"), 3);
		}
		else
			expanded = ft_strjoin_free(expanded, ft_substr(str, i, 1), 3);
		i++;
	}
	return (expanded);
}

char	*ft_expand_variable(t_cmd *cmd, char *str, int i)
{
	char	*expanded;
	char	*var_value;
	int		start;

	expanded = ft_strdup("");
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$' )
			i++;
		expanded = ft_strjoin_free(expanded,
				ft_substr(str, start, i - start), 3);
		if (str[i] == '$')
		{
			var_value = ft_expand_special_var(cmd, str, &i);
			if (var_value)
				expanded = ft_strjoin_free(expanded, var_value, 3);
		}
	}
	if (!expanded[0])
		cmd->num_args--;
	return (expanded);
}

static void	expand_item(t_cmd *cmd, char **item)
{
	char	*aux_ptr;

	if (ft_check_dolar(*item))
	{
		if (ft_check_special(*item))
		{
			aux_ptr = ft_expand_special(*item);
			free(*item);
			*item = ft_expand_variable(cmd, aux_ptr, 0);
			free(aux_ptr);
		}
		else if (ft_check_dolar_digit(*item))
		{
			aux_ptr = ft_expand_variable(cmd, *item, 0);
			free(*item);
			*item = aux_ptr;
		}
	}
}

void	ft_expand(t_cmd **cmd)
{
	int	i;

	expand_item(*cmd, &(*cmd)->cmd);
	if ((*cmd)->num_args == 0)
		return ;
	i = -1;
	while ((*cmd)->args[++i])
		expand_item(*cmd, &(*cmd)->args[i]);
}

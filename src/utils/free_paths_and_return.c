/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths_and_return.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:23:28 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/14 13:12:34 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

char	*free_paths_and_return(char **paths, char *to_return)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (to_return);
}

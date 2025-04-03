/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:49:51 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/10/03 18:23:37 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_realloc(void *buffer, size_t size)
{
	uint8_t	*new_buffer;
	uint8_t	*buffer_aux;
	size_t	i;

	buffer_aux = (uint8_t *) buffer;
	new_buffer = (uint8_t *) malloc (size * sizeof (uint8_t) + 1);
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (i < size && buffer_aux[i] && new_buffer[i])
	{
		new_buffer[i] = buffer_aux[i];
		i++;
	}
	free (buffer);
	return (new_buffer);
}

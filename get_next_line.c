/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:55:51 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/01 11:54:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_line(char *line_buffer)
{
	static size_t	i;
	char			*side_substr;

	i = 0;
	while (line_buffer[i] != '\0' || line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i] || !line_buffer[i + 1])
		return (NULL);
	side_substr = ft_substr(line_buffer, i - 1, ft_strlen(line_buffer));
	if (!side_substr)
	{
		free(side_substr);
		side_substr = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (side_substr);
}

static char	*fill_buffer(int fr, char *side_substr, char *buffer)
{
	
}

char	*get_next_line(int fd)
{

}

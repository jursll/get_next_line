/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:55:51 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/02 12:28:33 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *line)
{
	size_t	i;
	char	*side_str;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	side_str = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*side_str == '\0')
	{
		free(side_str);
		side_str = NULL;
	}
	line[i + 1] = '\0';
	return (side_str);
}

static char	*read_and_fill(int fd, char *buffer, char *side_str)
{
	char	*temp_buffer;
	int		read_line;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!side_str)
			side_str = ft_strdup("");
		temp_buffer = side_str;
		side_str = ft_strjoin(temp_buffer, buffer);
		free(temp_buffer);
		temp_buffer = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (side_str);
}

char	*get_next_line(int fd)
{
	static char	*side_str;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(side_str);
		side_str = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_and_fill(fd, buffer, side_str);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	side_str = extract_line(line);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test_fd.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}
	line = get_next_line(fd);
	while ((line != NULL ))
	{
		printf("%s\n", line);
		free(line);
	}
	if (close(fd) == -1)
	{
		perror("Erreur lors de la fermeture du fichier");
		return (1);
	}
	return (0);
}

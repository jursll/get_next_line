/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:33:03 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/07 23:07:29 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *left_stash, char *buf)
{
	ssize_t	nbytes;
	char	*tmp;

	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == - 1)
			return (free(left_stash), NULL);
		else if (nbytes == 0)
			break ;
		buf[nbytes] = '\n';
		if (!left_stash)
			left_stash = ft_strdup("");
		tmp = left_stash;
		left_stash = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (left_stash);
}

static char	*set_line(char *stash)
{
	char	*left_stash;
	ssize_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0 || stash[1] == 0)
        return (NULL);
	left_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	if (*left_stash == 0)
	{
		free(left_stash);
		left_stash = NULL;
	}
	stash[i + 1] = 0;
	return (left_stash);
}

char	*get_next_line(int fd)
{
	static char	*left_stash;
	char		*line;
	char		*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_stash);
		free(buf);
		left_stash = NULL;
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = read_and_stash(fd, left_stash, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	left_stash = set_line(line);
	return (line);
}

#include <fcntl.h>	// pour open
#include <stdio.h>	// pour printf
#include <string.h>	// pour strdup

int	main(void) // TEST POUR GET_NEXT_LINE
{
	int		fd;
	char	*result;

	fd = open("test_fd.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	result = get_next_line(fd);
	printf("%s", result);
	return (0);
}

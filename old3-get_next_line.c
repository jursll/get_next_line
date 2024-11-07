/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old3-get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:29:49 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/07 22:35:01 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash)
{
	ssize_t	nbytes;
	char	*buf;

	if (!stash)
		stash = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(stash), free(buf), NULL);
		buf[nbytes] = '\0';
		if (!nbytes)
			break ;
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free(buf), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

static char	*line_from_stash(char *prev_stash)
{
	int		i;
	char	*line;

	i = 0;
	while (prev_stash[i] && prev_stash[i] != '\n')
		i++;
	line = ft_substr(prev_stash, 0, i + 1);
	return (line);
}

static char	*clear_stash(char	*prev_stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (prev_stash[i] && prev_stash[i] != '\n')
		i++;
	if (!prev_stash)
		return(free(prev_stash), prev_stash = NULL, NULL);
	new_stash = ft_substr(prev_stash, i + 1, (ft_strlen(prev_stash) - i - 1));
	return (free(prev_stash), prev_stash = NULL, new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return(free(stash), stash = NULL, NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = line_from_stash(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = clear_stash(stash);
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
/*
int	main(void) // TEST POUR CLEAR STASH --> SEMI OK
{
	char *prev_stash = strdup("Hello\nDolly");

	printf("%s\n\n", prev_stash);
	printf("%s\n", clear_stash(prev_stash));
	free(prev_stash);
	return (0);
}

int	main(void) // TEST POUR LINE FROM STASH --> OK
{
	char *prev_stash = strdup("Hello\nDolly");

	printf("%s\n\n", prev_stash);
	printf("%s\n", line_from_stash(prev_stash));
	free(prev_stash);
	return (0);
}

int main(void) // TEST POUR READ_AND_STASH --> OK
{
	int fd = open("test_fd.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}

	char *stash = NULL;
	stash = read_and_stash(fd, stash);
	if (stash)
	{
		printf("Contenu du fichier:\n%s\n", stash);
		free(stash);
	}
	else
	{
		printf("Une erreur s'est produite lors de la lecture du fichier.\n");
	}

	close(fd);
	return (0);
}
*/

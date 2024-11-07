/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:36:31 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/07 11:08:42 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buf_to_stash(int fd, char *buf)
{
	static char	*stash;
	char		*temp;
	char		*search;
	int			stash_len;
	ssize_t		nbytes;

	stash = NULL;
	if (!stash)
		stash = ft_strdup("");
	stash_len = ft_strlen(stash);
	stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) + stash_len + 1));
	if(!stash)
		return (free(stash), stash = NULL, NULL);
	search = NULL;
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes < 0)
			return(free(stash), free(buf), NULL);
		temp = stash;
		stash = ft_strjoin(buf, temp);
		free(buf);
		free(temp);
		search = ft_strchr(stash, '\n');
		if (search)
			break;
	}
	return (stash);
}

static char	*line_from_stash(char *stash)
{
	int		i;
	char	*line;
	int		line_len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = ft_substr(stash, 0, i);
	line_len = ft_strlen(line);
	line[line_len] = '\0';
	return (line);
}

static char	*clear_stash(char *stash)
{
	char	*temp;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	temp = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	return (free(stash), stash = NULL, temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(buf), buf = NULL, NULL);
	stash = buf_to_stash(fd, buf);
	if (!stash)
		return (NULL);
	line = line_from_stash(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = clear_stash(stash);
	return (line);
}

/*
#include <stdio.h>

int	main(void) // TEST POUR CLEAR STASH - OK
{
	char *stash = ft_strdup("Hello\nDolly");

	printf("%s\n\n", stash);
	printf("%s\n", clear_stash(stash));
	free(stash);
	return (0);
}

int	main(void) // TEST POUR LINE FROM STASH - OK
{
	char *stash = ft_strdup("Hello\nDolly");

	printf("%s\n\n", stash);
	printf("%s\n", line_from_stash(stash));
	free(stash);
	return (0);
}

int	main(void) // TEST POUR BUF TO STASH - OK
{
	char *buf = ft_strdup("Dolly");

	printf("%s", buf_to_stash("Hello "));
	printf("%s", buf_to_stash(buf));
	free(buf);
	return (0);
}
*/

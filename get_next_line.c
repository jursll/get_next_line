/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:36:31 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/02 17:18:15 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buf_to_stash(char *buf)
{
	/*VOIR COMMENTAIRE DANS LA FONCTION GET_NEXT_LINE*/
	static char	*stash;
	char		*temp;
	int			stash_len;

	stash = NULL;
	if (!stash)
		stash = ft_strdup("");
	stash_len = ft_strlen(stash);
	temp = stash;
	stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) + stash_len + 1));
	if(!stash)
		return (free(stash), stash = NULL, NULL);
	stash = ft_strjoin(buf, temp);
	free(temp);
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
	char		*buf;
	char		*line;
	char		*final_line;
	ssize_t		nbytes;
	int			i;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(buf), buf = NULL, NULL);
	nbytes = 1;
	while (nbytes > 0)
	{
		/* Ici on a un pb car il nous manque une boucle pour lire et ajouter au stash
		tant qu'il n'y a pas de '\n', on devrait pouvoir corriger ça directement dans
		buf to stash (et ainsi gagner de la place dans get_next_line car on a déjà
		trop de variables anyways) - GOOD LUCK YOU CAN DO IT GURL*/
		nbytes = read(fd, buf, BUFFER_SIZE);
		stash = buf_to_stash(buf);
		line = line_from_stash(stash);
	}
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

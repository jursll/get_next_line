/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:36:31 by julrusse          #+#    #+#             */
/*   Updated: 2024/11/02 13:42:05 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static char	*stash_to_line(char *stash)
{
	int		i;
	char	*line;
	int		line_len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line = ft_substr(stash, 1, i);
	line_len = ft_strlen(line);
	line[line_len] = '\0';
	return (line);
}
*/
static char	*clear_stash(char *stash)
{
	char	*temp;
	int		i;
	int		stash_len;
	int		temp_len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (temp_len + 1));
	if (!temp)
		return (NULL);
	temp = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	temp_len = ft_strlen(temp);
	free(stash);
	stash = NULL;
	stash = (char *)malloc(sizeof(char) * (stash_len + 1));
	if (!stash)
		return (NULL);
	stash = ft_strdup(temp);
	stash_len = ft_strlen(stash);
	stash[stash_len] = '\0';
	return (stash);
}
/*
char	*get_next_line(int fd)
{
	static char	*file;
	char		*stash;
	char		*buf;
	char		*line;
	int			len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);


	stash = ft_strdup(buf);


}
*/

#include <stdio.h>

int	main(void)
{
	char *stash = [Hello\nDolly];
	char *line = NULL;

	printf("%s\n", stash);
	printf("%s\n", clear_stash(stash));
	return (0);
}

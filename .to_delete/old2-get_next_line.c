#include "get_next_line.h"

static char	*buf_to_stash(int fd, char *buf, char *stash)
{
	char		*stash_line;
	ssize_t		nbytes;

	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(stash), NULL);
		else if (nbytes == 0)
			break ;
		buf[nbytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		stash_line = ft_strjoin(stash, buf);
		if (!stash_line)
			break ;
		if (ft_strchr(stash_line, '\n'))
			break ;
	}
	free(buf);
	return (stash_line);
}

static char	*line_from_stash(char *stash_line)
{
	int		i;
	char	*final_line;;

	i = 0;
	while (stash_line[i] && stash_line[i] != '\n')
		i++;
	final_line = ft_substr(stash_line, 0, i + 1);
	return (final_line);
}

static char	*clear_stash(char *stash_line)
{
	char	*temp;
	int		i;

	i = 0;
	while (stash_line[i] && stash_line[i] != '\n')
		i++;
	if (!stash_line[i])
	{
		free(stash_line);
		stash_line = NULL;
		return (NULL);
	}
	temp = ft_substr(stash_line, i + 1, ft_strlen(stash_line) - i - 1);
	free(stash_line);
	stash_line = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*stash_line;
	char 		*final_line;
	char		*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return(free(stash), free(buf), stash = NULL, buf = NULL, NULL);
	if (!buf)
		return (NULL);
	stash_line = buf_to_stash(fd, buf, stash);
	if (!stash_line)
		return (NULL);
	final_line = line_from_stash(stash_line);
	if (!final_line)
		return (free(stash), stash = NULL, NULL);
	stash = clear_stash(stash_line);
	return (final_line);
}

/*
#include <stdio.h>
#include <fcntl.h> // pour open()

int	main(void) // TEST POUR GET_NEXT_LINE - KOOO
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
	int fd;
	char *buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

	fd = open("test_fd.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		free(buf);
		return (1);
	}

    // Simule un contenu initial pour `stash`
   // char *initial_stash = ft_strdup("hello\nworld");
   // printf("Initial stash: %s\n", initial_stash);

    // Appel de buf_to_stash pour tester le comportement
    char *result = buf_to_stash(fd, buf);
    printf("Result: %s\n", result);

    // Libération et fermeture des ressources
   // free(initial_stash);
    free(buf);
    close(fd);

    return (0);
}
*/

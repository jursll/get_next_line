#include "get_next_line.h"

#include <fcntl.h>	// pour open
#include <stdio.h>	// pour printf
#include <string.h>	// pour strdup

int main(void)
{
    int fd = open("test_fd.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}

/*
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
*/
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

char	*ft_strchr(char *s, int c)
{
	unsigned char	i;

	i = (unsigned char)c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (j + 1));
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

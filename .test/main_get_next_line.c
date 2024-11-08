
#include <fcntl.h>	// pour open
#include <stdio.h>	// pour printf
#include <string.h>	// pour strdup
#include "get_next_line.h"

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

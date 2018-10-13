/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** message transfer
*/

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "my_ftp.h"

void	send_server(const char *message, const int fd)
{
	size_t	size = strlen(message);
	char	buffer[size + 3];

	strcpy(buffer, message);
	strcpy(buffer + strlen(buffer) - 1, "\r\n");
	if (write(fd, buffer, strlen(buffer)) < 0) {
		logger_fmt(true, "write failed : %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

char	*receive_server(int fd)
{
	char	*buffer = malloc(sizeof(char) * BUFFER_SIZE);

	memset(buffer, 0, BUFFER_SIZE);
	if (read(fd, buffer, BUFFER_SIZE) < 0) {
		free(buffer);
		return (NULL);
	}
	if (strlen(buffer) > 2 && buffer[strlen(buffer) - 2] == '\r')
		buffer[strlen(buffer) - 2] = '\0';
	return (buffer);
}

int	get_answer(const char *code, int fd)
{
	char	*answer = receive_server(fd);

	if (answer == NULL)
		return (EXIT_FAILURE);
	puts(answer);
	fflush(stdout);
	if (strncmp(answer, code, strlen(code)) != 0)
		return (EXIT_FAILURE);
	free(answer);
	return (EXIT_SUCCESS);
}
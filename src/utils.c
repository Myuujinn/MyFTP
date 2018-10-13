/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Utils functions
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_ftp.h"

void	ffputs(const char *string)
{
	puts(string);
	fflush(stdout);
}

void	free_tokens(char **tokens)
{
	for (int i = 0; tokens[i] != NULL; ++i)
		free(tokens[i]);
	free(tokens);
}

char	*strdup_s(char *string)
{
	return (string == NULL ? NULL : strdup(string));
}

int	strcmp_s(const char *s1, const char *s2)
{
	return (s1 == NULL || s2 == NULL ? -1 : strcmp(s1, s2));
}

void	msg_client(const char *code, const char *message, int client_fd)
{
	size_t	size = strlen(code) + 1 + strlen(message);
	char	buffer[size + 4];

	strcpy(buffer, code);
	strcat(buffer, " ");
	strcat(buffer, message);
	buffer[size] = '\r';
	buffer[size + 1] = '\n';
	buffer[size + 2] = '\0';
	if (write(client_fd, buffer, strlen(buffer)) < 0)
		logger_fmt(true, "write failed : %s", strerror(errno));
}
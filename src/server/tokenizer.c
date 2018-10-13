/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Tokenizer
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

char	**receive_command(server_t *server)
{
	int	i = 1;
	char	buffer[BUFFER_SIZE];
	char	**tokens = malloc(sizeof(char **) * 2);

	if (fgets(buffer, BUFFER_SIZE, server->socket) == NULL)
		return (NULL);
	if (buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = '\0';
	if (buffer[strlen(buffer) - 1] == '\r')
		buffer[strlen(buffer) - 1] = '\0';
	tokens[0] = strdup_s(strtok(buffer, " "));
	if (tokens[0] == NULL)
		return (tokens);
	while (tokens[i - 1] != NULL) {
		tokens = realloc(tokens, sizeof(char **) * (i + 1));
		tokens[i] = strdup_s(strtok(NULL, " "));
		i += 1;
	}
	logger_fmt(false, "Received command [%s] from %s", tokens[0],
		server->ip_address);
	return (tokens);
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** TYPE command
*/

#include <server/server.h>
#include <string.h>

void	command_type(server_t *server, char **tokens)
{
	if (tokens[1] == NULL) {
		msg_client(FTP_500, FTP_NO_TYPE, server->client_fd);
		return;
	}
	if (strcmp(tokens[1], "I") != 0 && strcmp(tokens[1], "A") != 0)
	{
		msg_client(FTP_500, FTP_TYPE_ERR, server->client_fd);
		return;
	}
	msg_client(FTP_200, FTP_TYPE_SET, server->client_fd);
}
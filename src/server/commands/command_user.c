/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** USER command
*/

#include <string.h>
#include <stdlib.h>
#include "server/server.h"

void	command_user(server_t *server, char **tokens)
{
	if (server->logged) {
		msg_client(FTP_530, FTP_ALREADY_LOG, server->client_fd);
		return;
	}
	if (tokens[1] == NULL) {
		msg_client(FTP_332, FTP_NO_LOGIN, server->client_fd);
		return;
	}
	if (server->username != NULL)
		free(server->username);
	server->username = strdup(tokens[1]);
	msg_client(FTP_331, FTP_USER_OK, server->client_fd);
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** PASS command
*/

#include <string.h>
#include <server/server.h>
#include "server/server.h"

void	command_pass(server_t *server, char **tokens)
{
	if (server->username == NULL)
		msg_client(FTP_332, FTP_NO_LOGIN, server->client_fd);
	else if (server->logged)
		msg_client(FTP_530, FTP_ALREADY_LOG, server->client_fd);
	else if (strcasecmp(server->username, "anonymous") == 0
		&& tokens[1] == NULL) {
		msg_client(FTP_230, FTP_LOGGED, server->client_fd);
		server->logged = true;
	}
	else
		msg_client(FTP_530, FTP_BAD_PASS, server->client_fd);
}
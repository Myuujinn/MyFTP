/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** PWD command
*/

#include <server/server.h>

void	command_pwd(server_t *server, char **tokens)
{
	(void)tokens;
	if (!server->logged)
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
	else
		msg_client(FTP_257, server->cwd, server->client_fd);
}
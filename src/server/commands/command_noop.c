/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** NOOP command
*/

#include <server/server.h>

void	command_noop(server_t *server, char **tokens)
{
	(void)tokens;
	msg_client(FTP_200, FTP_NOOP_MSG, server->client_fd);
}
/*
** EPITECH PROJECT, 2018
** server
** File description:
** no command
*/

#include <server/server.h>
#include "server/server.h"

void	no_command(server_t *server)
{
	msg_client(FTP_500, FTP_UNKNOWN, server->client_fd);
}
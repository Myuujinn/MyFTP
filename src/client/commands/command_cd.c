/*
** EPITECH PROJECT, 2018
** server
** File description:
** cd client command
*/

#include <client/client.h>
#include "client/client.h"

void	command_cd(client_t *client, char **tokens)
{
	if (tokens[1] == NULL) {
		puts(FTP_HELP_CD);
		return;
	}
	msg_client(FTP_CWD, tokens[1], client->fd_server);
	get_answer(FTP_250, client->fd_server);
}
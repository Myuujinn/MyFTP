/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** pwd command
*/

#include <client/client.h>
#include "client/client.h"

void	command_pwd(client_t *client, char **tokens)
{
	msg_client(FTP_PWD, "", client->fd_server);
	get_answer(FTP_257, client->fd_server);
	(void)tokens;
}
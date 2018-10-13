/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Quit command
*/

#include "client/client.h"

void	command_quit(client_t *client, char **tokens)
{
	msg_client(FTP_QUIT, "", client->fd_server);
	client->should_exit = true;
	get_answer(FTP_221, client->fd_server);
	(void)tokens;
}
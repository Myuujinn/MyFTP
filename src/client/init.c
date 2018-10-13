/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Init functions for client
*/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "client.h"

static bool	is_ftp_server(client_t *client)
{
	return (get_answer(FTP_220, client->fd_server) == EXIT_SUCCESS ?
		true : false);
}

void	init_client(client_t *client, const char *ip, const char *port)
{
	client->ip = strdup(ip);
	client->port = strdup(port);
	client->username = NULL;
	client->fd_server = connect_to_server(ip, port);
	if (client->fd_server == -1)
		exit(EXIT_FAILURE);
	client->data_port = -1;
	client->mode = ACTIVE_MODE;
	client->should_exit = false;
	if (!is_ftp_server(client)) {
		logger("Target is not an FTP server.", true);
		exit(EXIT_FAILURE);
	}
}

void	free_client(client_t *client)
{
	if (client->ip != NULL)
		free(client->ip);
	if (client->port != NULL)
		free(client->port);
	if (client->username != NULL)
		free(client->username);
	if (client->fd_server != -1)
		close(client->fd_server);
}
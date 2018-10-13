/*
** EPITECH PROJECT, 2018
** client
** File description:
** passive and active mode
*/

#include <stdlib.h>
#include <string.h>
#include "client.h"

int	passive_mode(client_t *client)
{
	char	*answer = NULL;
	int	useless = -1;
	int	port1 = -1;
	int	port2 = -1;

	msg_client(FTP_PASV, "", client->fd_server);
	answer = receive_server(client->fd_server);
	ffputs(answer);
	if (strncmp(answer, FTP_227, strlen(FTP_227)) != 0) {
		free(answer);
		return (EXIT_FAILURE);
	}
	sscanf(answer, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).",
		&useless, &useless, &useless, &useless, &port1, &port2);
	if (port1 == -1 || port2 == -1) {
		free(answer);
		return (EXIT_FAILURE);
	}
	client->data_port = port1 * 256 + port2;
	free(answer);
	return (EXIT_SUCCESS);
}

static void	send_port(client_t *client)
{
	char	buffer[BUFFER_SIZE];
	int	ip1 = -1;
	int	ip2 = -1;
	int	ip3 = -1;
	int	ip4 = -1;

	memset(buffer, 0, BUFFER_SIZE);
	sscanf(client->ip, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
	snprintf(buffer, BUFFER_SIZE, "%d,%d,%d,%d,%d,%d", ip1, ip2, ip3, ip4,
		client->data_port / 256, client->data_port % 256);
	msg_client(FTP_PORT, buffer, client->fd_server);
}

int	active_mode(client_t *client)
{
	client->data_port = create_passive_socket(client);
	if (client->data_port == EXIT_FAILURE) {
		client->data_port = -1;
		return (EXIT_FAILURE);
	}
	send_port(client);
	if (get_answer(FTP_200, client->fd_server) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

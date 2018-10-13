/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Data socket manipulation
*/

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "client.h"

int	active_connect(client_t *client)
{
	struct protoent	*pe = getprotobyname("TCP");
	int		sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	int		useless = 1;
	struct sockaddr_in	addr = {0};

	if (sock == -1)
		return (-1);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
		(const char*)&useless, sizeof(useless)) == -1)
		return (-1);
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, client->ip, &(addr.sin_addr));
	addr.sin_port = htons((uint16_t)client->data_port);
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return (-1);
	client->fd_data = sock;
	return (0);
}

void	close_socket(client_t *client, int new_socket)
{
	if (client->fd_data != -1)
		close(client->fd_data);
	if (new_socket != -1)
		close(new_socket);
	client->fd_data = -1;
}

int	accept_client_data(client_t *client)
{
	struct sockaddr_in	addr;
	socklen_t		useless = sizeof(addr);
	int			new_socket = accept(client->fd_data,
		(struct sockaddr *)&addr, &useless);

	if (new_socket < 0) {
		close_socket(client, new_socket);
		return (-1);
	}
	return (new_socket);
}

int	create_passive_socket(client_t *client)
{
	struct sockaddr_in	addr;
	socklen_t		len = sizeof(addr);
	struct protoent		*pe = getprotobyname("TCP");

	client->fd_data = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (client->fd_data == -1)
		return (EXIT_FAILURE);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = 0;
	if (bind(client->fd_data, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return (EXIT_FAILURE);
	if (listen(client->fd_data, 1) == -1)
		return (EXIT_FAILURE);
	if (getsockname(client->fd_data, (struct sockaddr*)&addr, &len) == -1)
		return (EXIT_FAILURE);
	return (ntohs(addr.sin_port));
}
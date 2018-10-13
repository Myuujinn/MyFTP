/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Data socket manipulation
*/

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"

int	active_connect(server_t *server)
{
	struct protoent		*pe = getprotobyname("TCP");
	int 			useless = 1;
	int			sock;
	struct sockaddr_in	addr;

	if (pe == NULL)
		return (-1);
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock == -1)
		return (-1);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
		(const char *)&useless, sizeof(useless)) == -1)
		return (-1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(server->ip_address);
	addr.sin_port = htons((uint16_t)server->port);
	if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
		return (-1);
	server->data_fd = sock;
	return (0);
}

int	accept_client_data(server_t *server)
{
	struct sockaddr_in	addr;
	socklen_t		useless = sizeof(addr);
	int			new_socket = accept(server->data_fd,
		(struct sockaddr *)&addr, &useless);

	if (new_socket < 0) {
		close_socket(server, new_socket);
		return (-1);
	}
	return (new_socket);
}

int	create_passive_socket(server_t *server)
{
	struct sockaddr_in	addr;
	socklen_t		len = sizeof(addr);
	struct protoent		*pe = getprotobyname("TCP");

	server->data_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (server->data_fd == -1)
		return (-1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = 0;
	if (bind(server->data_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		return (-1);
	if (listen(server->data_fd, 1) == -1)
		return (-1);
	if (getsockname(server->data_fd, (struct sockaddr*)&addr, &len) == -1)
		return (-1);
	return (ntohs(addr.sin_port));
}

void	close_socket(server_t *server, int new_socket)
{
	if (server->data_fd != -1)
		close(server->data_fd);
	if (new_socket != -1)
		close(new_socket);
	server->mode = NO_MODE;
	server->data_fd = -1;
}
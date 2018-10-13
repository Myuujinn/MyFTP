/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** PORT command
*/

#include <server/server.h>
#include <string.h>

static int	parse_port(char *token)
{
	unsigned int	useless = 0;
	int	port1 = -1;
	int	port2 = -1;

	sscanf(token, "%u,%u,%u,%u,%d,%d",
		&useless, &useless, &useless, &useless, &port1, &port2);
	if (port1 <= 0 || port2 < 0)
		return (-1);
	return (port1 * 256 + port2);
}

void	command_port(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (tokens[1] == NULL) {
		msg_client(FTP_520, FTP_NO_PORT, server->client_fd);
		return;
	}
	server->port = parse_port(tokens[1]);
	if (server->port == -1) {
		msg_client(FTP_520, FTP_NO_PORT, server->client_fd);
		return;
	}
	server->data_fd = -1;
	server->mode = ACTIVE_MODE;
	msg_client(FTP_200, FTP_PORT_MSG, server->client_fd);
}
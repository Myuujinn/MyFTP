/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** PASV command
*/

#include <unistd.h>
#include <netdb.h>
#include <server/server.h>
#include <string.h>

static void	passive_msg(server_t *server)
{
	char		msg[BUFFER_SIZE];
	unsigned int	ip1 = 0;
	unsigned int	ip2 = 0;
	unsigned int	ip3 = 0;
	unsigned int	ip4 = 0;

	memset(msg, 0, BUFFER_SIZE);
	sscanf(server->ip_address, "%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);
	snprintf(msg, BUFFER_SIZE, "%s (%d,%d,%d,%d,%d,%d).", FTP_PASV_MSG,
		ip1, ip2, ip3, ip4, server->port / 256, server->port % 256);
	msg_client(FTP_227, msg, server->client_fd);
}

void	command_pasv(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (server->data_fd != -1)
		close(server->data_fd);
	server->port = create_passive_socket(server);
	if (server->port == -1) {
		msg_client(FTP_520, FTP_PASV_FAIL, server->client_fd);
		server->mode = NO_MODE;
		server->data_fd = -1;
	}
	passive_msg(server);
	server->mode = PASSIVE_MODE;
	(void)tokens;
}
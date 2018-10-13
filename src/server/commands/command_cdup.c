/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** CDUP command
*/

#include <server/server.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	command_cdup(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (chdir("../") < 0) {
		msg_client(FTP_550, FTP_BAD_CWD, server->client_fd);
		return;
	}
	if (check_if_in_base_dir(server) == EXIT_SUCCESS)
		msg_client(FTP_250, FTP_CWD_MSG, server->client_fd);
	(void)tokens;
}
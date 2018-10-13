/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** CWD command
*/

#include <server/server.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	check_if_in_base_dir(server_t *server)
{
	char	*new_path = realpath("./", NULL);

	if (strncmp(new_path, server->base_directory,
		strlen(server->base_directory)) != 0) {
		free(new_path);
		chdir(server->cwd);
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return (EXIT_FAILURE);
	}
	free(server->cwd);
	server->cwd = new_path;
	return (EXIT_SUCCESS);
}

void	command_cwd(server_t *server, char **tokens)
{
	(void)tokens;
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (tokens[1] == NULL) {
		msg_client(FTP_550, FTP_BAD_CWD, server->client_fd);
		return;
	}
	if (chdir(tokens[1]) < 0) {
		msg_client(FTP_550, FTP_BAD_CWD, server->client_fd);
		return;
	}
	if (check_if_in_base_dir(server) == EXIT_SUCCESS)
		msg_client(FTP_250, FTP_CWD_MSG, server->client_fd);
}
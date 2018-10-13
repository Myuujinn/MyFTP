/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** DELE command
*/

#include <server/server.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char	*get_file_path(server_t *server, const char *token)
{
	char		file_path[strlen(server->cwd) + strlen(token) + 2];
	char		*real_path;

	strcpy(file_path, server->cwd);
	strcat(file_path, "/");
	strcat(file_path, token);
	real_path = realpath(file_path, NULL);
	if (real_path == NULL)
		return (NULL);
	if (strncmp(real_path, server->base_directory,
		strlen(server->base_directory)) != 0) {
		free(real_path);
		return (NULL);
	}
	return (real_path);
}

static int	remove_file(server_t *server, char *file_path)
{
	if (file_path == NULL || access(file_path, F_OK) != 0) {
		msg_client(FTP_550, FTP_DELE_FAIL, server->client_fd);
		return (EXIT_FAILURE);
	}
	if (remove(file_path) == -1) {
		msg_client(FTP_550, strerror(errno), server->client_fd);
		free(file_path);
		return (EXIT_FAILURE);
	}
	free(file_path);
	return (EXIT_SUCCESS);
}

void	command_dele(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (tokens[1] == NULL) {
		msg_client(FTP_550, FTP_DELE_FAIL, server->client_fd);
		return;
	}
	if (remove_file(server, get_file_path(server, tokens[1]))
		== EXIT_SUCCESS)
		msg_client(FTP_250, FTP_DELE_MSG, server->client_fd);
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** RETR command
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
	#include "server/server.h"

static void	send_file(int fd_file, int fd_serv)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read = 0;

	if (fd_file == -1)
		return;
	bytes_read = read(fd_file, buffer, BUFFER_SIZE);
	while (bytes_read > 0) {
		write(fd_serv, buffer, (unsigned)bytes_read);
		bytes_read = read(fd_file, buffer, BUFFER_SIZE);
	}
	close(fd_file);
}

static void	retr_passive(server_t *server, const char *path)
{
	int	new_socket = accept_client_data(server);
	char	*real_path = get_file_path(server, path);

	if (new_socket == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	if (real_path == NULL) {
		msg_client(FTP_550, FTP_NO_DIR, server->client_fd);
		return;
	}
	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	send_file(open(real_path, O_RDONLY), new_socket);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, new_socket);
}

static void	retr_active(server_t *server, const char *path)
{
	char	*real_path = get_file_path(server, path);

	if (active_connect(server) == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	if (real_path == NULL) {
		msg_client(FTP_550, FTP_NO_DIR, server->client_fd);
		close_socket(server, -1);
		return;
	}
	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	send_file(open(real_path, O_RDONLY), server->data_fd);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, -1);
}

static int	readable_file(server_t *server, const char *file_path)
{
	char	*real_path = get_file_path(server, file_path);

	if (real_path == NULL)
		return (EXIT_FAILURE);
	if (access(real_path, R_OK) != 0) {
		free(real_path);
		return (EXIT_FAILURE);
	}
	free(real_path);
	return (EXIT_SUCCESS);
}

void	command_retr(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (server->mode == NO_MODE) {
		msg_client(FTP_425, FTP_NO_MODE, server->client_fd);
		return;
	}
	if (tokens[1] == NULL) {
		msg_client(FTP_550, FTP_NO_RETR, server->client_fd);
		return;
	}
	if (readable_file(server, tokens[1]) == EXIT_FAILURE)
		msg_client(FTP_550, FTP_FILE_FAIL, server->client_fd);
	else if (server->mode == PASSIVE_MODE)
		retr_passive(server, tokens[1]);
	else if (server->mode == ACTIVE_MODE)
		retr_active(server, tokens[1]);
}
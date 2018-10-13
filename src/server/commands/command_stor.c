/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** STOR command
*/

#include <unistd.h>
#include <fcntl.h>
#include <server/server.h>
#include <string.h>
#include <errno.h>

static void	write_file(int fd_serv, const char *name)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read = 0;
	int	fd_file = creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd_file == -1) {
		logger_fmt(true, "creat failed : %s", strerror(errno));
		return;
	}
	bytes_read = read(fd_serv, buffer, BUFFER_SIZE);
	while (bytes_read > 0) {
		write(fd_file, buffer, (unsigned)bytes_read);
		bytes_read = read(fd_serv, buffer, BUFFER_SIZE);
	}
	close(fd_file);
}

static void	retr_passive(server_t *server, const char *name)
{
	int	new_socket = accept_client_data(server);

	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	if (new_socket == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	write_file(new_socket, name);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, new_socket);
}

static void	retr_active(server_t *server, const char *name)
{
	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	if (active_connect(server) == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	write_file(server->data_fd, name);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, -1);
}

void	command_stor(server_t *server, char **tokens)
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
		msg_client(FTP_550, FTP_NO_STOR, server->client_fd);
		return;
	}
	if (server->mode == PASSIVE_MODE)
		retr_passive(server, tokens[1]);
	else if (server->mode == ACTIVE_MODE)
		retr_active(server, tokens[1]);
}
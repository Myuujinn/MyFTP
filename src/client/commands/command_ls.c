/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ls client command
*/

#include <stdlib.h>
#include <unistd.h>
#include <client/client.h>
#include "client/client.h"

static void	passive_ls(client_t *client, const char *path)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	read_bytes;

	msg_client(FTP_LIST, path != NULL ? path : "",
		client->fd_server);
	if (active_connect(client) == EXIT_FAILURE)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	read_bytes = read(client->fd_data, buffer, BUFFER_SIZE);
	while (read_bytes > 0) {
		write(STDOUT_FILENO, buffer, (unsigned)read_bytes);
		read_bytes = read(client->fd_data, buffer, BUFFER_SIZE);
	}
	close_socket(client, -1);
	get_answer(FTP_226, client->fd_server);
}

static void	active_ls(client_t *client, const char *path)
{
	int	fd = -1;
	char	buffer[BUFFER_SIZE];
	ssize_t	read_bytes;

	msg_client(FTP_LIST, path != NULL ? path : "",
		client->fd_server);
	fd = accept_client_data(client);
	if (fd == -1)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0) {
		write(STDOUT_FILENO, buffer, (unsigned)read_bytes);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	close_socket(client, fd);
	get_answer(FTP_226, client->fd_server);
}

void	command_ls(client_t *client, char **tokens)
{
	if (client->mode == PASSIVE_MODE) {
		if (passive_mode(client) == EXIT_SUCCESS)
			passive_ls(client, tokens[1]);
	} else {
		if (active_mode(client) == EXIT_SUCCESS)
			active_ls(client, tokens[1]);
	}
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** 
*/


#include <stdlib.h>
#include <unistd.h>
#include <client/client.h>
#include <fcntl.h>
#include "client/client.h"

static void	put(const char *path, int fd_serv)
{
	char	buffer[BUFFER_SIZE];
	int	fd = open(path, O_RDONLY);
	ssize_t	read_bytes;

	if (fd == -1)
		return;
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0) {
		write(fd_serv, buffer, (unsigned)read_bytes);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
}

static void	passive_put(client_t *client, const char *name,
		const char *path)
{
	msg_client(FTP_STOR, name, client->fd_server);
	if (active_connect(client) == EXIT_FAILURE)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	put(path, client->fd_data);
	close_socket(client, -1);
	get_answer(FTP_226, client->fd_server);
}

static void	active_put(client_t *client, const char *name, const char *path)
{
	int	fd = -1;

	msg_client(FTP_STOR, name, client->fd_server);
	fd = accept_client_data(client);
	if (fd == -1)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	put(path, fd);
	close_socket(client, fd);
	get_answer(FTP_226, client->fd_server);
}

void	command_put(client_t *client, char **tokens)
{
	if (tokens[1] == NULL || tokens[2] == NULL) {
		puts("Specify file to send and file name on server.");
		return;
	}
	if (client->mode == PASSIVE_MODE) {
		if (passive_mode(client) == EXIT_SUCCESS)
			passive_put(client, tokens[2], tokens[1]);
	} else {
		if (active_mode(client) == EXIT_SUCCESS)
			active_put(client, tokens[2], tokens[1]);
	}
}
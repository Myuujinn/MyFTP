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

static void	get(const char *path, int fd_serv)
{
	char	buffer[BUFFER_SIZE];
	int	fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ssize_t	read_bytes;

	if (fd == -1)
		return;
	read_bytes = read(fd_serv, buffer, BUFFER_SIZE);
	while (read_bytes > 0) {
		write(fd, buffer, (unsigned)read_bytes);
		read_bytes = read(fd_serv, buffer, BUFFER_SIZE);
	}
}

static void	passive_get(client_t *client, const char *path)
{
	msg_client(FTP_RETR, path, client->fd_server);
	if (active_connect(client) == EXIT_FAILURE)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	get(path, client->fd_data);
	close_socket(client, -1);
	get_answer(FTP_226, client->fd_server);
}

static void	active_get(client_t *client, const char *path)
{
	int	fd;

	msg_client(FTP_RETR, path, client->fd_server);
	fd = accept_client_data(client);
	if (fd == -1)
		return;
	if (get_answer(FTP_150, client->fd_server) == EXIT_FAILURE)
		return;
	get(path, fd);
	close_socket(client, fd);
	get_answer(FTP_226, client->fd_server);
}

void	command_get(client_t *client, char **tokens)
{
	if (tokens[1] == NULL) {
		puts("Specify file to send and file name on server.");
		return;
	}
	if (client->mode == PASSIVE_MODE) {
		if (passive_mode(client) == EXIT_SUCCESS)
			passive_get(client, tokens[1]);
	} else {
		if (active_mode(client) == EXIT_SUCCESS)
			active_get(client, tokens[1]);
	}
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Server functions
*/

#include <my_ftp.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "server.h"

static int	listen_for_connections(int fd, const char *port)
{
	if (fd == -1) {
		logger(SERVER_COULD_NOT_START_ERROR, true);
		return (EXIT_FAILURE);
	}
	if (listen(fd, MAX_CLIENTS) < 0) {
		logger(strerror(errno), true);
		return (EXIT_FAILURE);
	}
	logger(SERVER_STARTED, false);
	logger_fmt(false, "%s %s", LISTENING_ON_PORT, port);
	return (EXIT_SUCCESS);
}

static int	fork_client(int client_fd, int fd,
		struct sockaddr_in *client_addr, const char *cwd)
{
	pid_t	pid = fork();

	if (pid < 0) {
		logger_fmt(true, "fork failed : %s", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0) {
		close(fd);
		if (handle_client(client_fd, client_addr, cwd) == EXIT_FAILURE)
		{
			close(client_fd);
			logger_fmt(true, SOMETHING_WRONG_ERROR);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	close(client_fd);
	return (EXIT_SUCCESS);
}

int	server_loop(int fd, struct sockaddr_in *client_addr, const char *cwd)
{
	socklen_t	client_size = sizeof(client_addr);
	int		fd_client = accept(fd, (struct sockaddr *)client_addr,
			&client_size);

	if (fd_client == -1) {
		logger_fmt(true, "accept failed : %s", strerror(errno));
		return (EXIT_FAILURE);
	}
	logger_fmt(false, "Incoming connection from %s",
		inet_ntoa(client_addr->sin_addr));
	if (fork_client(fd_client, fd, client_addr, cwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	server(const char *port, const char *cwd)
{
	struct sockaddr_in	client_addr;
	int			status = EXIT_SUCCESS;
	int 			fd = create_server_socket(port);

	if (listen_for_connections(fd, port) == EXIT_FAILURE) {
		close(fd);
		return (EXIT_FAILURE);
	}
	while (42)
		if (server_loop(fd, &client_addr, cwd) == EXIT_FAILURE) {
			status = EXIT_FAILURE;
			logger(SOMETHING_WRONG_ERROR, true);
			break;
		}
	close(fd);
	return (status);
}
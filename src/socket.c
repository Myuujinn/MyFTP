/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Socket manipulation functions
*/

#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "my_ftp.h"

static int	bind_to_socket(int fd, struct addrinfo *address_info)
{
	int	useless = 1;

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &useless,
		sizeof(useless)) < 0)
		logger_fmt(true, "setsockopt failed : %s", strerror(errno));
	if (bind(fd, address_info->ai_addr, address_info->ai_addrlen) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	bind_or_connect(int fd, struct addrinfo *address_info,
		bool is_server)
{
	if (fd > 0) {
		if (is_server) {
			if (bind_to_socket(fd, address_info) == 0)
				return (EXIT_SUCCESS);
		} else {
			if (connect(fd, address_info->ai_addr,
				address_info->ai_addrlen) != -1)
				return (EXIT_SUCCESS);
		}
		close(fd);
	}
	return (EXIT_FAILURE);

}

static int	find_fd_from_socket(struct addrinfo *address_info,
		bool is_server)
{
	int		fd = -1;
	struct addrinfo *saved_info = address_info;

	while (address_info) {
		fd = socket(address_info->ai_family, address_info->ai_socktype,
			address_info->ai_protocol);
		if (bind_or_connect(fd, address_info, is_server) == 0)
			break;
		address_info = address_info->ai_next;
	}
	ASSERT_RETURN(address_info != NULL,
		error_return("Couldn't find any address.", -1));
	freeaddrinfo(saved_info);
	return (fd);
}

int	connect_to_server(const char *host, const char *port)
{
	struct addrinfo	hint;
	struct addrinfo	*address_info;
	int		error;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	if (host == NULL)
		hint.ai_flags = AI_PASSIVE;
	error = getaddrinfo(host, port, &hint, &address_info);
	ASSERT_RETURN(error == 0, error_return(gai_strerror(error), -1));
	return (find_fd_from_socket(address_info, host == NULL ? true : false));
}

int	create_server_socket(const char *port)
{
	return (connect_to_server(NULL, port));
}
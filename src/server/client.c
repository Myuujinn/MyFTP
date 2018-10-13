/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Functions to handle client
*/

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

static ftp_commands_t	commands_g[] = {
	{FTP_USER, &command_user},
	{FTP_PASS, &command_pass},
	{FTP_CWD, &command_cwd},
	{FTP_CDUP, &command_cdup},
	{FTP_QUIT, &command_quit},
	{FTP_DELE, &command_dele},
	{FTP_PWD, &command_pwd},
	{FTP_PASV, &command_pasv},
	{FTP_PORT, &command_port},
	{FTP_HELP, &command_help},
	{FTP_NOOP, &command_noop},
	{FTP_RETR, &command_retr},
	{FTP_STOR, &command_stor},
	{FTP_LIST, &command_list},
	{FTP_TYPE, &command_type},
	{NULL, NULL}
};

static void	init_client(server_t *server, int client_fd,
		struct sockaddr_in *client_addr, const char *cwd)
{
	server->cwd = realpath(cwd, NULL);
	server->base_directory = realpath(cwd, NULL);
	server->username = NULL;
	server->password = NULL;
	server->ip_address = inet_ntoa(client_addr->sin_addr);
	server->client_fd = client_fd;
	server->socket = fdopen(client_fd, "r");
	server->data_fd = -1;
	server->mode = NO_MODE;
	server->logged = false;
	server->quit = false;
	chdir(cwd);
}

static void	free_client(server_t *server)
{
	free(server->cwd);
	free(server->base_directory);
	if (server->username != NULL)
		free(server->username);
	if (server->password != NULL)
		free(server->password);
	if (server->socket != NULL)
		fclose(server->socket);
	if (server->client_fd != -1)
		close(server->client_fd);
	if (server->data_fd != -1)
		close(server->data_fd);
}

static void	find_command(server_t *server, char **tokens)
{
	for (int i = 0; commands_g[i].id != NULL; ++i) {
		if (strcmp_s(tokens[0], commands_g[i].id) == 0) {
			commands_g[i].command(server, tokens);
			return;
		}
	}
	no_command(server);
}

int	handle_client(int client_fd, struct sockaddr_in *client_addr,
	const char *cwd)
{
	server_t	server;
	char		**tokens = NULL;

	init_client(&server, client_fd, client_addr, cwd);
	msg_client(FTP_220, FTP_HELLO, server.client_fd);
	while (!server.quit) {
		tokens = receive_command(&server);
		if (tokens == NULL)
			return (EXIT_FAILURE);
		find_command(&server, tokens);
		free_tokens(tokens);
	}
	msg_client(FTP_221, FTP_BYE, client_fd);
	logger_fmt(false, "Client %s exited.", server.ip_address);
	free_client(&server);
	return (EXIT_SUCCESS);
}
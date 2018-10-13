/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** HELP command
*/

#include <server/server.h>
#include <string.h>

static void	help_msg2(server_t *server, const char *command)
{
	if (strcmp(command, "PWD") == 0)
		msg_client(FTP_214, FTP_HELP_PWD, server->client_fd);
	else if (strcmp(command, "QUIT") == 0)
		msg_client(FTP_214, FTP_HELP_QUIT, server->client_fd);
	else if (strcmp(command, "RETR") == 0)
		msg_client(FTP_214, FTP_HELP_RETR, server->client_fd);
	else if (strcmp(command, "STOR") == 0)
		msg_client(FTP_214, FTP_HELP_STOR, server->client_fd);
	else if (strcmp(command, "USER") == 0)
		msg_client(FTP_214, FTP_HELP_USER, server->client_fd);
	else if (strcmp(command, "TYPE") == 0)
		msg_client(FTP_214, FTP_HELP_TYPE, server->client_fd);
	else
		msg_client(FTP_214, FTP_HELP_MSG, server->client_fd);
}

static void	help_msg(server_t *server, const char *command)
{
	if (strcmp(command, "CDUP") == 0)
		msg_client(FTP_214, FTP_HELP_CDUP, server->client_fd);
	else if (strcmp(command, "CWD") == 0)
		msg_client(FTP_214, FTP_HELP_CWD, server->client_fd);
	else if (strcmp(command, "DELE") == 0)
		msg_client(FTP_214, FTP_HELP_DELE, server->client_fd);
	else if (strcmp(command, "HELP") == 0)
		msg_client(FTP_214, FTP_HELP_HELP, server->client_fd);
	else if (strcmp(command, "LIST") == 0)
		msg_client(FTP_214, FTP_HELP_LIST, server->client_fd);
	else if (strcmp(command, "NOOP") == 0)
		msg_client(FTP_214, FTP_HELP_NOOP, server->client_fd);
	else if (strcmp(command, "PASS") == 0)
		msg_client(FTP_214, FTP_HELP_PASS, server->client_fd);
	else if (strcmp(command, "PASV") == 0)
		msg_client(FTP_214, FTP_HELP_PASV, server->client_fd);
	else if (strcmp(command, "PORT") == 0)
		msg_client(FTP_214, FTP_HELP_PORT, server->client_fd);
	else
		help_msg2(server, command);
}

void	command_help(server_t *server, char **tokens)
{
	if (tokens[1] == NULL) {
		msg_client(FTP_214, FTP_HELP_MSG, server->client_fd);
		return;
	}
	help_msg(server, tokens[1]);
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** LIST command
*/

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include "server/server.h"

static void	exec_ls(const char *path, int fd)
{
	int	save_stdout = dup(STDOUT_FILENO);
	pid_t	pid;

	dup2(fd, STDOUT_FILENO);
	pid = fork();
	if (pid == 0) {
		if (path == NULL)
			execl("/bin/ls", "ls", "-l", NULL);
		else
			execl("/bin/ls", "ls", "-l", path, NULL);
		exit(EXIT_SUCCESS);
	} else
		waitpid(pid, 0, WSTOPPED);
	dup2(save_stdout, STDOUT_FILENO);
}

static void	list_passive(server_t *server, const char *path)
{
	int	new_socket = accept_client_data(server);

	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	if (new_socket == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	exec_ls(path, new_socket);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, new_socket);
}

static void	list_active(server_t *server, const char *path)
{
	msg_client(FTP_150, FTP_OPEN_BIN, server->client_fd);
	if (active_connect(server) == -1) {
		msg_client(FTP_520, FTP_FAIL_CLIENT, server->client_fd);
		return;
	}
	exec_ls(path, server->data_fd);
	msg_client(FTP_226, FTP_TRSF_COMPL, server->client_fd);
	close_socket(server, -1);
}

void	command_list(server_t *server, char **tokens)
{
	if (!server->logged) {
		msg_client(FTP_530, FTP_DENIED, server->client_fd);
		return;
	}
	if (server->mode == NO_MODE) {
		msg_client(FTP_425, FTP_NO_MODE, server->client_fd);
		return;
	}
	if (server->mode == PASSIVE_MODE)
		list_passive(server, tokens[1]);
	else if (server->mode == ACTIVE_MODE)
		list_active(server, tokens[1]);
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Authentication of client
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "client.h"

static char	*get_password(const char *prompt)
{
	struct termios	old;
	struct termios	new;
	char		*password;

	fputs(prompt, stdout);
	if (tcgetattr(STDIN_FILENO, &old) != 0)
		exit(EXIT_FAILURE);
	new = old;
	new.c_lflag &= ~ECHO;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new) != 0)
		exit(EXIT_FAILURE);
	password = get_input();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
	ffputs("");
	return (password);
}

static int	auth_username(client_t *client)
{
	do {
		if (client->username != NULL)
			free(client->username);
		fputs("Username : ", stdout);
		fflush(stdout);
		client->username = get_input();
		if (client->username == NULL)
			exit(EXIT_FAILURE);
	} while (strlen(client->username) <= 0);
	msg_client(FTP_USER, client->username, client->fd_server);
	if (get_answer(FTP_331, client->fd_server) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	send_pass(client_t *client, char *pass)
{
	msg_client(FTP_PASS, pass, client->fd_server);
	if (get_answer(FTP_230, client->fd_server) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(pass);
	return (EXIT_SUCCESS);
}

static int	auth_password(client_t *client)
{
	char	*password = get_password("Password : ");

	if (password == NULL) {
		free(password);
		return (EXIT_FAILURE);
	}
	return (send_pass(client, password));
}

void	authenticate(client_t *client)
{
	do {
		while (auth_username(client) != EXIT_SUCCESS);
	} while (auth_password(client) != EXIT_SUCCESS);
}
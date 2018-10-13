/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** QUIT command
*/

#include <server/server.h>

void	command_quit(server_t *server, char **tokens)
{
	(void)tokens;
	server->quit = true;
}
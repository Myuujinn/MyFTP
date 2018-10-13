/*
** EPITECH PROJECT, 2018
** server
** File description:
** command_clear.c
*/

#include <stdlib.h>
#include "client/client.h"

void	command_clear(client_t *client, char **tokens)
{
	(void)client;
	(void)tokens;
	system("clear");
}
/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** passive command
*/

#include <client/client.h>
#include "client/client.h"

void	command_passive(client_t *client, char **tokens)
{
	if (client->mode == ACTIVE_MODE) {
		client->mode = PASSIVE_MODE;
		puts("Passive mode ON.");
	} else {
		client->mode = ACTIVE_MODE;
		puts("Passive mode OFF.");
	}
	(void)tokens;
}
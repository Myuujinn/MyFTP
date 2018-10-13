/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Client
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my_ftp.h"
#include "client.h"

static ftp_commands_t	commands_g[] = {
	{"cd", &command_cd},
	{"clear", &command_clear},
	{"exit", &command_quit},
	{"help", &command_help},
	{"get", &command_get},
	{"ls", &command_ls},
	{"passive", &command_passive},
	{"pasv", &command_passive},
	{"put", &command_put},
	{"pwd", &command_pwd},
	{"quit", &command_quit},
	{NULL, NULL}
};

void	command_help(client_t *client, char **tokens)
{
	for (int i = 0; commands_g[i].id != NULL; ++i)
		display_help(commands_g[i].id);
	(void)tokens;
	(void)client;
}

static void	prompt(client_t *client)
{
	printf("[" ANSI_COLOR_GREEN "MyFTP" ANSI_COLOR_RESET
		"] [" ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET
		"@" ANSI_COLOR_YELLOW "%s:%s" ANSI_COLOR_RESET "] > ",
		client->username, client->ip, client->port);
	fflush(stdout);
}

static void	find_command(client_t *client, char **tokens)
{
	for (int i = 0; commands_g[i].id != NULL; ++i) {
		if (strcmp(tokens[0], commands_g[i].id) == 0) {
			commands_g[i].command(client, tokens);
			return;
		}
	}
	ffputs("Unknown command."
	" Type \"help\" for a list of available commands.");
}

static void	client_loop(client_t *client)
{
	char 	*input = NULL;
	char 	**tokens = NULL;

	while (!client->should_exit) {
		prompt(client);
		input = get_input();
		if (input == NULL) {
			puts("");
			command_quit(client, NULL);
			return;
		}
		tokens = tokenizer(input);
		if (tokens != NULL) {
			find_command(client, tokens);
			free_tokens(tokens);
		}
	}
}

void	client(const char *ip, const char *port)
{
	client_t	client;

	init_client(&client, ip, port);
	authenticate(&client);
	client_loop(&client);
	free_client(&client);
}
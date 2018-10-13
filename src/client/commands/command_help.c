/*
** EPITECH PROJECT, 2018
** server
** File description:
** help command
*/

#include <stdio.h>
#include <string.h>
#include "client/client.h"

static ftp_help_t	help_g[] = {
	{"clear", FTP_HELP_CLEAR},
	{"cd", FTP_HELP_CD},
	{"get", FTP_HELP_GET},
	{"help", FTP_HELP_HELP},
	{"ls", FTP_HELP_LS},
	{"passive", FTP_HELP_PASV},
	{"put", FTP_HELP_PUT},
	{"pwd", FTP_HELP_PWD},
	{"quit", FTP_HELP_QUIT},
	{NULL, NULL}
};

void	display_help(const char *cmd)
{
	for (int i = 0; help_g[i].id != NULL; ++i)
		if (strcmp(cmd, help_g[i].id) == 0) {
			puts(help_g[i].help);
			return;
		}
}
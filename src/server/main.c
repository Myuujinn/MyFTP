/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Main
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "server.h"

const char *program_name;

static void	usage(bool is_error)
{
	FILE *stream = is_error ? stderr : stdout;
	fprintf(stream, "USAGE:\t%s port path\n", program_name);
	fprintf(stream, "\tport\tis the port number on which the server socket"
		" listens\n");
	fprintf(stream, "\tpath\tis the path to the home directory for the"
		" Anonymous user\n");
}

bool	is_dir(const char *dir)
{
	struct stat	file_stat;

	if (stat(dir, &file_stat) == -1)
		return (false);
	return (S_ISDIR(file_stat.st_mode));
}

int	main(int argc, char *argv[])
{
	program_name = argv[0];
	if (argc > 1 && strcmp("-help", argv[1]) == 0) {
		usage(false);
		return (EXIT_SUCCESS);
	}
	if (argc < 3 || argc > 3 || !is_dir(argv[2])) {
		usage(true);
		return (EXIT_FAILURE);
	}
	if (server(argv[1], argv[2]) == EXIT_FAILURE) {
		logger(SERVER_ERROR, true);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
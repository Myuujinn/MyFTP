/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Main
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "my_ftp.h"

const char	*program_name;

void	usage(bool isError)
{
	FILE *stream = isError ? stderr : stdout;
	fprintf(stream, "USAGE:\n\t%s <ip> <port>\n", program_name);
}

int	main(int argc, char *argv[])
{
	program_name = argv[0];
	if (argc < 3 || argc > 3) {
		usage(true);
		return (EXIT_FAILURE);
	}
	client(argv[1], argv[2]);
	return (EXIT_SUCCESS);
}
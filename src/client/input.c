/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Input manipulation functions
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_ftp.h"

char	*get_input(void)
{
	char	*buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);

	if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		return (NULL);
	if (buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = '\0';
	return (buffer);
}
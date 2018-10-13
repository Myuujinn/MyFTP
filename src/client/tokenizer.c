/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Tokenizer
*/

#include <stdlib.h>
#include <string.h>
#include "my_ftp.h"

char	**tokenizer(char *input)
{
	int	i = 1;
	char	**tokens = malloc(sizeof(char **) * 2);

	tokens[0] = strdup_s(strtok(input, " "));
	if (tokens[0] == NULL)
		return (NULL);
	while (tokens[i - 1] != NULL) {
		tokens = realloc(tokens, sizeof(char **) * (i + 1));
		tokens[i] = strdup_s(strtok(NULL, " "));
		i += 1;
	}
	free(input);
	return (tokens);
}
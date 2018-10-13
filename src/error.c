/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Error functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_ftp.h"

void	print_error(const char *error)
{
	logger(error, true);
}

int	error_return(const char *error, int return_value)
{
	print_error(error);
	return (return_value);
}

void	*error_ptr(const char *error, void *ptr)
{
	print_error(error);
	return (ptr);
}

void	error_exit(const char *error)
{
	print_error(error);
	exit(EXIT_FAILURE);
}
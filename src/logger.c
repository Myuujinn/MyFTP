/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Logger for server
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include "my_ftp.h"

static void	get_time(char *buffer)
{
	time_t		raw_time;
	struct tm	*time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);
	snprintf(buffer, BUFFER_SIZE, "%02d/%02d/%04d %02d:%02d:%02d",
		time_info->tm_mday, time_info->tm_mon + 1,
		time_info->tm_year + 1900, time_info->tm_hour,
		time_info->tm_min, time_info->tm_sec);
}

void	logger_fmt(bool is_error, const char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE];

	va_start(args, format);
	vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);
	logger(buffer, is_error);
}

void	logger(const char *message, bool is_error)
{
	char	time[BUFFER_SIZE];

	get_time(time);
	if (is_error)
		fprintf(stderr, ANSI_COLOR_GREEN "[MyFTP] " ANSI_COLOR_RESET \
		ANSI_COLOR_RED "[%s] - %s\n" ANSI_COLOR_RESET, time, message);
	else
		printf(ANSI_COLOR_GREEN "[MyFTP] " ANSI_COLOR_RESET \
		ANSI_COLOR_RED "[%s]" ANSI_COLOR_RESET \
		" - %s\n", time, message);
}
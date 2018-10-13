/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Header file for global my_ftp functions
*/

#pragma once

#include <stdbool.h>

#undef	EXIT_FAILURE
#define	EXIT_FAILURE		84

#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"

#define MAX_PORT_SIZE		5
#define BUFFER_SIZE		1024

#define ASSERT(x)		if (!(x)) return;
#define ASSERT_RETURN(x, y)	if (!(x)) return (y);

#define FTP_150		"150"
#define FTP_200		"200"
#define FTP_214		"214"
#define FTP_220		"220"
#define FTP_221		"221"
#define FTP_226		"226"
#define FTP_227		"227"
#define FTP_230		"230"
#define FTP_250		"250"
#define FTP_257		"257"
#define FTP_331		"331"
#define FTP_332		"332"
#define FTP_425		"425"
#define FTP_500		"500"
#define FTP_501		"501"
#define FTP_520		"520"
#define FTP_530		"530"
#define FTP_550		"550"

#define FTP_CDUP	"CDUP"
#define FTP_CWD		"CWD"
#define FTP_DELE	"DELE"
#define FTP_HELP	"HELP"
#define	FTP_LIST	"LIST"
#define FTP_NOOP	"NOOP"
#define FTP_PASS	"PASS"
#define FTP_PASV	"PASV"
#define FTP_PORT	"PORT"
#define FTP_PWD		"PWD"
#define FTP_QUIT	"QUIT"
#define FTP_RETR	"RETR"
#define FTP_STOR	"STOR"
#define FTP_TYPE	"TYPE"
#define FTP_USER	"USER"

typedef enum {
	NO_MODE,
	ACTIVE_MODE,
	PASSIVE_MODE
}	file_transfer_mode_t;

extern const char *program_name;

int	create_server_socket(const char *port);
int	connect_to_server(const char *host, const char *port);

void	msg_client(const char *code, const char *message, int client_fd);
char	*strdup_s(char *string);
int	strcmp_s(const char *s1, const char *s2);
void	ffputs(const char *string);
void	free_tokens(char **tokens);


void	logger(const char *message, bool is_error);
void	logger_fmt(bool is_error, const char *format, ...);
void	print_error(const char *error);
int	error_return(const char *error, int return_value);
void	*error_ptr(const char *error, void *ptr);
void	error_exit(const char *error);

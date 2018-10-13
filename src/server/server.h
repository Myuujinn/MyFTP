/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Header for my_ftp server
*/

#pragma once

#include <netinet/in.h>

#include <stdio.h>
#include "my_ftp.h"

#define MAX_CLIENTS	100

#undef	EXIT_FAILURE
#define	EXIT_FAILURE	84

#define SERVER_ERROR	"An error occurred. Server is shutting down."
#define SERVER_COULD_NOT_START_ERROR	"Couldn't start server."
#define SOMETHING_WRONG_ERROR	"Something went wrong. Closing connection."
#define SERVER_STARTED	"Server started."
#define SERVER_STOPPED	"Stopping server."
#define LISTENING_ON_PORT	"Listening on port"

#define FTP_HELLO	"Hello there."
#define FTP_BYE		"Goodbye."
#define FTP_USER_OK	"User OK, need password."
#define FTP_ANON_ONLY	"This server is anonymous only."
#define FTP_NO_LOGIN	"No login specified"
#define FTP_ALREADY_LOG	"Already logged in."
#define	FTP_LOGGED	"Logged in, proceed."
#define FTP_DENIED	"Permission denied."
#define FTP_BAD_PASS	"Bad password."
#define FTP_HELP_MSG	"Use HELP <command> to see how to use it."
#define FTP_PASV_MSG	"Entering Passive Mode"
#define FTP_PASV_FAIL	"Failed to enter Passive Mode."
#define FTP_NO_MODE	"Use PORT or PASV first."
#define FTP_UNKNOWN	"Unknown command."
#define FTP_BAD_CWD	"Failed to change directory."
#define FTP_NO_DIR	"No such file or directory."
#define FTP_CWD_MSG	"Successfully changed directory."
#define FTP_NOOP_MSG	"No operation."
#define FTP_OPEN_BIN	"Opening BINARY mode data connection"
#define FTP_TRSF_COMPL	"Transfer complete."
#define FTP_FAIL_CLIENT	"Impossible to reach client."
#define FTP_NO_PORT	"Please specify an IP address and port."
#define FTP_PORT_MSG	"Entering Active Mode"
#define FTP_DELE_FAIL	"Specify a file to delete."
#define FTP_DELE_MSG	"Successfully deleted file."
#define FTP_NO_RETR	"Specify a file to retrieve."
#define FTP_NO_STOR	"Specify a name for the file to store."
#define FTP_NO_TYPE	"Specitfy a type."
#define FTP_TYPE_ERR	"This server only supports type I"
#define FTP_TYPE_SET	"Type successfully set."
#define FTP_FILE_FAIL	"No such file / Can't read file."

#define FTP_HELP_CDUP	"CDUP - Moves one directory up."
#define FTP_HELP_CWD	"CWD <directory> - Change working directory."
#define FTP_HELP_DELE	"DELE <file> - Delete file."
#define FTP_HELP_HELP	"HELP <command> - Displays the help for the command."
#define FTP_HELP_LIST	"LIST - Lists the content of the directory."
#define FTP_HELP_NOOP	"NOOP - No operation."
#define FTP_HELP_PASS	"PASS <password> - Enter password."
#define FTP_HELP_PASV	"PASV - Enter Passive Mode."
#define FTP_HELP_PORT	"PORT <port> - Enter Active Mode on port <port>."
#define FTP_HELP_PWD	"PWD - Print working directory."
#define FTP_HELP_QUIT	"QUIT - Quits the current session."
#define FTP_HELP_RETR	"RETR <file> - Retreive file from server."
#define FTP_HELP_STOR	"STOR <local_file> - Store local file to server."
#define FTP_HELP_TYPE	"TYPE <type> - Specify type."
#define FTP_HELP_USER	"USER <username> - Login with <username>."

typedef struct {
	char			*cwd;
	char			*base_directory;
	char			*username;
	char			*password;
	char			*ip_address;
	int			port;
	int			client_fd;
	FILE			*socket;
	int			data_fd;
	file_transfer_mode_t	mode;
	bool			logged;
	bool			quit;
}	server_t;

typedef void (*ftp_command_t)(server_t *, char **);

typedef struct {
	char		*id;
	ftp_command_t	command;
}	ftp_commands_t;

bool	is_dir(const char *dir);
int	server(const char *port, const char *cwd);
int	handle_client(int client_fd, struct sockaddr_in *client_addr,
	const char *cwd);
int	create_passive_socket(server_t *server);
void	close_socket(server_t *server, int new_socket);
int	accept_client_data(server_t *server);
int	active_connect(server_t *server);
char	*get_file_path(server_t *server, const char *token);
char	**receive_command(server_t *server);

void	no_command(server_t *server);
void	command_cdup(server_t *server, char **tokens);
void	command_cwd(server_t *server, char **tokens);
int	check_if_in_base_dir(server_t *server);
void	command_dele(server_t *server, char **tokens);
void	command_help(server_t *server, char **tokens);
void	command_list(server_t *server, char **tokens);
void	command_noop(server_t *server, char **tokens);
void	command_pass(server_t *server, char **tokens);
void	command_pasv(server_t *server, char **tokens);
void	command_port(server_t *server, char **tokens);
void	command_pwd(server_t *server, char **tokens);
void	command_quit(server_t *server, char **tokens);
void	command_retr(server_t *server, char **tokens);
void	command_stor(server_t *server, char **tokens);
void	command_type(server_t *server, char **tokens);
void	command_user(server_t *server, char **tokens);


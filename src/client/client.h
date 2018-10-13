/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Client header
*/

#pragma once

#include <stdio.h>
#include "my_ftp.h"

#define FTP_HELP_CD	"cd <path> - Change directory to <path>."
#define FTP_HELP_CLEAR	"clear - Clear terminal."
#define FTP_HELP_GET	"get <server_file> - Get file from server."
#define FTP_HELP_HELP	"help - Display help."
#define FTP_HELP_LS	"ls [<path>] - List files in the chosen directory."
#define FTP_HELP_PASV	"passive/pasv - Toggle Passive Mode."
#define FTP_HELP_PUT	"put <local_file> - Put local file in server."
#define FTP_HELP_PWD	"pwd - Print working directory."
#define FTP_HELP_QUIT	"quit/exit - Exit client."

typedef struct {
	char			*ip;
	char			*port;
	char			*username;
	int			fd_server;
	int			data_port;
	int			fd_data;
	file_transfer_mode_t	mode;
	bool			should_exit;
}	client_t;

typedef void (*ftp_command_t)(client_t *, char **);

typedef struct {
	char		*id;
	ftp_command_t	command;
}	ftp_commands_t;

typedef struct {
	char		*id;
	char		*help;
}	ftp_help_t;

void	init_client(client_t *client, const char *ip, const char *port);
void	free_client(client_t *client);
void	client(const char *ip, const char *port);
char	*receive_server(int fd);
void	send_server(const char *message, int fd);
void	authenticate(client_t *client);
char	*get_input(void);
int	get_answer(const char *code, int fd);
char	**tokenizer(char *input);
void	display_help(const char *cmd);
int	passive_mode(client_t *client);
int	active_mode(client_t *client);
void	close_socket(client_t *client, int new_socket);
int	active_connect(client_t *client);
int	create_passive_socket(client_t *client);
int	accept_client_data(client_t *client);

void	command_cd(client_t *client, char **tokens);
void	command_clear(client_t *client, char **tokens);
void	command_get(client_t *client, char **tokens);
void	command_ls(client_t *client, char **tokens);
void	command_quit(client_t *client, char **tokens);
void	command_pwd(client_t *client, char **tokens);
void	command_put(client_t *client, char **tokens);
void	command_passive(client_t *client, char **tokens);
void	command_help(client_t *client, char **tokens);
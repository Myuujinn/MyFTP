##
## EPITECH PROJECT, 2018
## myftp
## File description:
## Makefile
##

NAME_CLIENT	=	myftp

DIR_SRC		=	src/

DIR_CLIENT	=	$(DIR_SRC)client/

SRC_CLIENT	=	$(DIR_CLIENT)main.c			\
			$(DIR_CLIENT)client.c			\
			$(DIR_CLIENT)msg_transfer.c		\
			$(DIR_CLIENT)init.c			\
			$(DIR_CLIENT)auth.c			\
			$(DIR_CLIENT)input.c			\
			$(DIR_CLIENT)tokenizer.c		\
			$(DIR_CLIENT)pasv_actv.c		\
			$(DIR_CLIENT)socket_data.c		\
			$(DIR_CLIENT)commands/command_cd.c	\
			$(DIR_CLIENT)commands/command_clear.c	\
			$(DIR_CLIENT)commands/command_get.c	\
			$(DIR_CLIENT)commands/command_ls.c	\
			$(DIR_CLIENT)commands/command_quit.c	\
			$(DIR_CLIENT)commands/command_pwd.c	\
			$(DIR_CLIENT)commands/command_passive.c	\
			$(DIR_CLIENT)commands/command_put.c	\
			$(DIR_CLIENT)commands/command_help.c	\
			$(DIR_SRC)socket.c			\
			$(DIR_SRC)error.c			\
			$(DIR_SRC)logger.c			\
			$(DIR_SRC)utils.c

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	server

DIR_SERVER	=	$(DIR_SRC)server/

SRC_SERVER	=	$(DIR_SERVER)main.c			\
			$(DIR_SERVER)server.c			\
			$(DIR_SERVER)client.c			\
			$(DIR_SERVER)socket_data.c		\
			$(DIR_SERVER)tokenizer.c		\
			$(DIR_SERVER)commands/command_cdup.c	\
			$(DIR_SERVER)commands/command_cwd.c	\
			$(DIR_SERVER)commands/command_dele.c	\
			$(DIR_SERVER)commands/command_help.c	\
			$(DIR_SERVER)commands/command_list.c	\
			$(DIR_SERVER)commands/command_noop.c	\
			$(DIR_SERVER)commands/command_pass.c	\
			$(DIR_SERVER)commands/command_pasv.c	\
			$(DIR_SERVER)commands/command_port.c	\
			$(DIR_SERVER)commands/command_pwd.c	\
			$(DIR_SERVER)commands/command_quit.c	\
			$(DIR_SERVER)commands/command_retr.c	\
			$(DIR_SERVER)commands/command_stor.c	\
			$(DIR_SERVER)commands/command_type.c	\
			$(DIR_SERVER)commands/command_user.c	\
			$(DIR_SERVER)commands/no_command.c	\
			$(DIR_SRC)utils.c			\
			$(DIR_SRC)logger.c			\
			$(DIR_SRC)socket.c			\
			$(DIR_SRC)error.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

INC		=	-I $(DIR_SRC)

LIBS		=	

CFLAGS		+=	-W -Wall -Wextra -std=gnu11 $(INC)

LDFLAGS		+=	$(LIBS)

all:			$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_CLIENT):		$(OBJ_CLIENT)
			$(CC) $(OBJ_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

$(NAME_SERVER):		$(OBJ_SERVER)
			$(CC) $(OBJ_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

clean:
			$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)

fclean:			clean
			$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re:			fclean all

.PHONY:			clean fclean re all

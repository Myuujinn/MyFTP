cmake_minimum_required(VERSION 3.10)
project(client C)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(src/)

add_executable(server src/my_ftp.h src/server/tokenizer.c
        src/server/server.h src/logger.c src/socket.c
        src/error.c src/server/server.c src/server/client.c
        src/server/commands/command_cdup.c
        src/server/commands/command_cwd.c
        src/server/commands/command_dele.c
        src/server/commands/command_help.c
        src/server/commands/command_list.c
        src/server/commands/command_noop.c
        src/server/commands/command_pass.c
        src/server/commands/command_pasv.c
        src/server/commands/command_port.c
        src/server/commands/command_pwd.c
        src/server/commands/command_quit.c
        src/server/commands/command_retr.c
        src/server/commands/command_stor.c
        src/server/commands/command_user.c
        src/server/commands/command_type.c
        src/server/socket_data.c
        src/utils.c
        src/server/main.c
        src/server/tokenizer.c src/server/commands/no_command.c)
add_executable(client src/client/client.c src/client/main.c
        src/client/client.h src/client/msg_transfer.c
        src/client/init.c src/client/auth.c
        src/client/input.c src/client/commands/command_ls.c
        src/client/tokenizer.c
        src/client/commands/command_quit.c src/client/commands/command_pwd.c
        src/client/commands/command_passive.c
        src/client/commands/command_help.c
        src/client/socket_data.c src/client/pasv_actv.c
        src/my_ftp.h src/logger.c src/socket.c
        src/error.c src/utils.c src/client/commands/command_clear.c src/client/commands/command_cd.c)
NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g
# CFLAGS = -g

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_H = libft/include

SRC_DIR = src

SIGNAL_C = src/signal/set_sig_dfl.c src/signal/set_sig_handler.c src/signal/set_sig_ign.c \
			src/signal/set_signal.c src/signal/set_terminal.c src/signal/sig_handler.c

LEXING_C = src/lexing/get_word.c src/lexing/lexing_list.c src/lexing/lexing_proc.c

CMD_LIST_C = src/cmd_list/cmd_free.c src/cmd_list/listing_cmd.c src/cmd_list/listing_util.c src/cmd_list/quoting_util.c \
			src/cmd_list/quoting.c src/cmd_list/setting_fds.c

HEREDOC_C = src/heredoc/do_heredoc.c src/heredoc/heredoc_util.c src/heredoc/heredoc.c

EXECVE_C = src/execve/cmd_path.c src/execve/exe_cmds.c src/execve/exe_util.c src/execve/handle_error.c \
			src/execve/handle_status.c src/execve/redirection.c src/execve/set_builtin.c src/execve/util_builtin.c

CMDQUOTING_C = src/cmd_quoting/env_extend.c src/cmd_quoting/extending_lexer_list.c src/cmd_quoting/extending_util.c \
			src/cmd_quoting/quotting_lexer_list.c

BUILTIN_C = src/built-in/builtin_exe_p.c src/built-in/cd_util.c src/built-in/cd.c src/built-in/echo.c src/built-in/env.c \
			src/built-in/exit_util.c src/built-in/exit.c src/built-in/export.c src/built-in/pwd.c src/built-in/unset.c

ENV_C = src/env/env_to_envp.c src/env/env_util.c src/env/envp_to_env.c


SIGNAL_O = obj/signal/set_sig_dfl.o obj/signal/set_sig_handler.o obj/signal/set_sig_ign.o \
			obj/signal/set_signal.o obj/signal/set_terminal.o obj/signal/sig_handler.o

LEXING_O = obj/lexing/get_word.o obj/lexing/lexing_list.o obj/lexing/lexing_proc.o

CMD_LIST_O = obj/cmd_list/cmd_free.o obj/cmd_list/listing_cmd.o obj/cmd_list/listing_util.o obj/cmd_list/quoting_util.o \
			obj/cmd_list/quoting.o obj/cmd_list/setting_fds.o

HEREDOC_O = obj/heredoc/do_heredoc.o obj/heredoc/heredoc_util.o obj/heredoc/heredoc.o

EXECVE_O = obj/execve/cmd_path.o obj/execve/exe_cmds.o obj/execve/exe_util.o obj/execve/handle_error.o \
			obj/execve/handle_status.o obj/execve/redirection.o obj/execve/set_builtin.o obj/execve/util_builtin.o

CMDQUOTING_O = obj/cmd_quoting/env_extend.o obj/cmd_quoting/extending_lexer_list.o obj/cmd_quoting/extending_util.o \
			obj/cmd_quoting/quotting_lexer_list.o

BUILTIN_O = obj/built-in/builtin_exe_p.o obj/built-in/cd_util.o obj/built-in/cd.o obj/built-in/echo.o obj/built-in/env.o \
			obj/built-in/exit_util.o obj/built-in/exit.o obj/built-in/export.o obj/built-in/pwd.o obj/built-in/unset.o

ENV_O = obj/env/env_to_envp.o obj/env/env_util.o obj/env/envp_to_env.o

OBJ_DIR = obj
INC_DIR = include

SRCS = $(SIGNAL_C) $(LEXING_C) $(CMD_LIST_C) $(HEREDOC_C) \
		$(EXECVE_C) $(CMDQUOTING_C) $(ENV_C) $(BUILTIN_C) src/initialize.c \
		src/minishell.c src/util.c src/valid.c

OBJS = $(SIGNAL_O) $(LEXING_O) $(CMD_LIST_O) $(HEREDOC_O) \
		$(EXECVE_O) $(CMDQUOTING_O) $(ENV_O) $(BUILTIN_O) obj/initialize.o \
		obj/minishell.o obj/util.o obj/valid.o

INCLUDES = -I$(LIBFT_H) -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT_LIB)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re

NAME = minishell

CC = cc

# CFLAGS = -wall -werror -wextra
CFLAGS = -g

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_H = libft/include

SRC_DIR = src
SIGNAL_DIR = src/signal
LEXING_DIR = src/lexing
QUOTING_DIR = src/quoting
CMD_LIST_DIR = src/cmd_list
HEREDOC_DIR = src/heredoc
OBJ_DIR = obj
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SIGNAL_DIR)/*.c) $(wildcard $(LEXING_DIR)/*.c) $(wildcard $(QUOTING_DIR)/*.c) $(wildcard $(CMD_LIST_DIR)/*.c) $(wildcard $(HEREDOC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

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

CC = cc
NAME = minishell
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

SRC = Main/main.c
SRC += Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c
SRC += Leaks/free_all.c Leaks/garbedge.c
SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
	@sleep 1
	@echo "\033[0;32mcreating the minishell is Done!\033[0m"

clean:
	@rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@sleep 1
	@echo "\033[0;31mremoving minishell is Done!\033[0m"

re: fclean all

.PHONY: all clean fclean re


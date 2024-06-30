CC = cc
NAME = minishell

# CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
#------------------
SRC = Main/main.c
SRC +=  Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c
SRC += Leaks/free_all.c Leaks/garbedge.c
SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c
#------------------

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ) #LIBFT/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -Llibft -lft
	@sleep 1
	@echo "\033[0;32mcreating the minishell is Done!\033[0m"
# libft/libft.a:
# 	$(MAKE) -C libft
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@sleep 1
	@echo "\033[0;31mremoving minishell is Done!\033[0m"
re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ)

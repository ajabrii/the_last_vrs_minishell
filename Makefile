# CC = cc
# NAME = minishell
# LIBFT_DIR = Libft
# LIBFT = $(LIBFT_DIR)/libft.a

# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# SRC = Main/main.c
# SRC += Builtins/env.c Builtins/exit.c
# SRC += Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c
# SRC += Leaks/free_all.c Leaks/garbedge.c
# SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c
# SRC += Executer/ft_execute.c

# GREEN = \033[0;32m
# RED = \033[0;31m
# YELLOW = \033[0;33m
# NC = \033[0m

# # ASCII Art
# NEOSHELL_ART = "\n\
# ${GREEN}  _   _            _____ _          _ _ ${NC}\n\
# ${GREEN} | \\ | |          / ____| |        | | |${NC}\n\
# ${GREEN} |  \\| | ___  ___| (___ | |__   ___| | |${NC}\n\
# ${GREEN} ||/ _ \\/ _ \\\\___ \\| '_ \\ / _ \\ | |${NC}\n\
# ${GREEN} | |\\  |  __/ (_) |___) | | | |  __/ | |${NC}\n\
# ${GREEN} |_| \\_|\\___|\\___/_____/|_| |_|\\___|_|_|${NC}\n\
# ${GREEN}                                        ${NC}\n\
# ${GREEN}                                        ${NC}\n"

# OBJ = $(SRC:.c=.o)

# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(MAKE) -C $(LIBFT_DIR) bonus

# $(NAME): $(LIBFT) $(OBJ)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
# 	@sleep 1
# 	@echo "\033[0;32mcreating the minishell is Done!\033[0m"
# 	@echo -e "$(NEOSHELL_ART)"

# clean:
# 	@rm -rf $(OBJ)
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	@rm -rf $(NAME)
# 	$(MAKE) -C $(LIBFT_DIR) fclean
# 	@sleep 1
# 	@echo "\033[0;31mremoving minishell is Done!\033[0m"

# re: fclean all

# .PHONY: all clean fclean re



# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# Project name
NAME = minishell

# Directories
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = Main/main.c
SRC += Builtins/env.c Builtins/exit.c
SRC += Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c
SRC += Leaks/free_all.c Leaks/garbedge.c
SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c
SRC += Executer/ft_execute.c

# Object files
OBJ = $(SRC:.c=.o)

# Colors
GREEN = \033[1;32m
GREEN_BOLD = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
NC = \033[0m

# Targets
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Building Libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
	@sleep 1
	@echo "${GREEN_BOLD}Creating minishell is Done!${NC}"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@sleep 1
	@echo "$(RED)Removing minishell is Done!${NC}"

re: fclean all

# Phony targets
.PHONY: all clean fclean re

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# Project name
NAME = minishell

# Directories
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = Main/main.c Main/mtools.c
SRC += Builtins/env.c Builtins/exit.c Builtins/echo.c Builtins/export.c
SRC += Builtins/pwd.c Builtins/unset.c Builtins/get_set.c Builtins/cd.c
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

ASCII_ART = "\
\n\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
"
# ASCII_ART = "\
# \n\
# ███╗   ██╗███████╗ ██████╗ \n\
# ████╗  ██║██╔════╝██╔════╝ \n\
# ██╔██╗ ██║█████╗  ██║  ███╗\n\
# ██║╚██╗██║██╔══╝  ██║   ██║\n\
# ██║ ╚████║███████╗╚██████╔╝\n\
# ╚═╝  ╚═══╝╚══════╝ ╚═════╝ \n\
# "
# Targets
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Building Libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
	@echo $(ASCII_ART)
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

#########################################33

# CC = cc
# CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

# # Project name
# NAME = minishell

# # Directories
# LIBFT_DIR = Libft
# LIBFT = $(LIBFT_DIR)/libft.a

# # Source files
# SRC = Main/main.c Main/mtools.c
# SRC += Builtins/env.c Builtins/exit.c
# SRC += Lexer/lexical.c Lexer/lextools.c Lexer/token.c Lexer/lex_utils.c
# SRC += Leaks/free_all.c Leaks/garbedge.c
# SRC += Parser/ft_parser.c Parser/putils.c Parser/tools.c
# SRC += Executer/ft_execute.c

# # Object files
# OBJ = $(SRC:.c=.o)

# # Colors
# GREEN = \033[1;32m
# GREEN_BOLD = \033[1;32m
# RED = \033[1;31m
# YELLOW = \033[1;33m
# NC = \033[0m

# # ASCII Art
# ASCII_ART = "\
# \n\
# ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
# ████╗ ████║██║████╗  ██║██║██╔════╝██║ ██╔╝██╔════╝██║     ██║     \n\
# ██╔████╔██║██║██╔██╗ ██║██║███████╗█████╔╝ █████╗  ██║     ██║     \n\
# ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔═██╗ ██╔══╝  ██║     ██║     \n\
# ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██╗███████╗███████╗███████╗\n\
# ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
# "

# # Targets
# all:
# 	@echo $(ASCII_ART)
# 	@$(MAKE) $(LIBFT) $(NAME)

# $(LIBFT):
# 	@echo "$(YELLOW)Building Libft...$(NC)"
# 	@$(MAKE) -C $(LIBFT_DIR)
# 	@$(MAKE) -C $(LIBFT_DIR) bonus

# $(NAME): $(LIBFT) $(OBJ)
# 	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
# 	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L$(LIBFT_DIR) -lft
# 	@sleep 1
# 	@echo "$(GREEN_BOLD}Creating minishell is Done!$(NC)"

# clean:
# 	@echo "$(RED)Cleaning object files...$(NC)"
# 	@rm -rf $(OBJ)
# 	@$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	@echo "$(RED)Removing $(NAME)...$(NC)"
# 	@rm -rf $(NAME)
# 	@$(MAKE) -C $(LIBFT_DIR) fclean
# 	@sleep 1
# 	@echo "$(RED)Removing minishell is Done!$(NC)"

# re: fclean all

# # Phony targets
# .PHONY: all clean fclean re

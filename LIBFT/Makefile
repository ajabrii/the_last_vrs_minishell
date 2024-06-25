
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source File PART 1
SOURCE = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_tolower.c
SOURCE += ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_toupper.c
SOURCE += ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c
# Source File PART 2
SOURCE += ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c
SOURCE += ft_putnbr_fd.c ft_strmapi.c ft_striteri.c
# Object files
OBJ = $(SOURCE:.c=.o)
# Target library
NAME = libft.a
O_BNS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJ_BNS = $(O_BNS:.c=.o)

# Build rules

all: $(NAME)
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "creating the libft.a is Done"
$(OBJ):$(SOURCE)
	cc $(CFLAGS) -c $(SOURCE)
 
bonus:	$(OBJ_BNS)
	
$(OBJ_BNS):$(O_BNS)
	cc $(CFLAGS) -c $(O_BNS)
	@ar rc $(NAME) $(OBJ_BNS)

clean:
	@rm -f $(OBJ) $(OBJ_BNS)

fclean: clean
	@rm -f $(NAME)
	@echo "removing the libft.a in progress ..."

re: fclean all

.PHONY: fclean all clean re bonus
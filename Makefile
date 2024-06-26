SRC = 	gcc Main/*.c Leaks/*.c Lexer/*.c LIBFT/*.c Parser/*.c
FLAG = -lreadline -fsanitize=address -g3

all:
	$(SRC) $(FLAG)

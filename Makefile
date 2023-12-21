NAME			= minishell

SRCC_DIR		= src/
BUILTIN_DIR 	= builtin/

BUILTIN 		= pwd.c \
				cd.c \
				exit.c \
				env.c \
				echo.c \
				export.c \
				unset.c

SRCS			= main.c \
				utils.c \
				parse.c \
				exec.c \
				ft_split.c \
				isbuilt.c \
				mem_tools.c \
				debug.c

CC 				= cc

CFLAGS			= -Wextra -Wall -Werror -g3

LINK 			= -lreadline

HEADERS			= header/minishell.h

OBJ_DIR = OBJ/

vpath %.c $(SRCC_DIR) $(BUILTIN_DIR)

BUILTIN_SRCS 	= $(addprefix $(BUILTIN_DIR), $(BUILTIN))
OBJ_PATH 		= $(SRCC_DIR)$(OBJ_DIR)

SRCS			+= $(BUILTIN)
OBJ 			= $(patsubst %.c, $(OBJ_PATH)%.o, $(SRCS))
OBJ_BUILTIN		= $(patsubst %.c, $(OBJ_PATH)%.o, $(BUILTIN))

all : $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -I . -o $(NAME) $(LINK)

$(OBJ_PATH)%.o : $(BUILTIN_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o : %.c $(OBJ_BUILTIN) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean re fclean

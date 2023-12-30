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
				isbuilt.c \
				mem_tools.c \
				cmd_list.c \
				fd_redirection.c \
				multichecking.c \
				str_edit.c \
				split_command.c \
				debug.c

CC 				= cc

CFLAGS			= -Wextra -Wall -Werror -gdwarf-4

LINK 			= -lreadline

HEADERS			= header/minishell.h

LIB_DIR = lib/libft/
LIB = lib/libft.a

OBJ_DIR = OBJ/

vpath %.c $(SRCC_DIR) $(BUILTIN_DIR)

BUILTIN_SRCS 	= $(addprefix $(BUILTIN_DIR), $(BUILTIN))
OBJ_PATH 		= $(SRCC_DIR)$(OBJ_DIR)

SRCS			+= $(BUILTIN)
OBJ 			= $(patsubst %.c, $(OBJ_PATH)%.o, $(SRCS))
OBJ_BUILTIN		= $(patsubst %.c, $(OBJ_PATH)%.o, $(BUILTIN))

all : $(NAME)

$(NAME): $(OBJ) $(LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -I . -o $(NAME) $(LINK)

$(OBJ_PATH)%.o : $(BUILTIN_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o : %.c $(OBJ_BUILTIN) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): force
	@make -sC $(LIB_DIR)

clean :
	rm -f $(OBJ)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re : fclean all

.PHONY: all clean re fclean force

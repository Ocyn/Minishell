NAME			= minishell

SRCC_DIR		= src/
BUILTIN_DIR 	= builtin/
MEMORY_DIR 		= memory/

BUILTIN 		= pwd.c \
				cd.c \
				exit.c \
				env.c \
				echo.c \
				export.c \
				unset.c

MEMORY			= cmd_list.c \
	 			memory_allocation.c \
				quick_checking.c \
				memory_edit.c \
				memory_scan.c \
				split_command.c \
				very_sure.c \
				query.c 

SRCS			= main.c \
				signal.c \
				readline.c \
				utils.c \
				parse.c \
				exec.c \
				isbuilt.c \
				fd_redirection.c \
				build_command.c \
				heredoc.c \
				new_heredoc.c \
				prompt_tuning.c \
				debug.c

CC 				= cc

CFLAGS			= -Wextra -Wall -Werror -gdwarf-4

LINK 			= -lreadline

HEADERS			= header/minishell.h

LIB_DIR = lib/libft/
LIB = lib/libft.a

OBJ_DIR = OBJ/

vpath %.c $(SRCC_DIR) $(BUILTIN_DIR) $(MEMORY_DIR)

MEMORY_SRCS 	= $(addprefix $(MEMORY_DIR), $(BUILTIN))
BUILTIN_SRCS 	= $(addprefix $(BUILTIN_DIR), $(BUILTIN))
OBJ_PATH 		= $(SRCC_DIR)$(OBJ_DIR)

SRCS			+= $(BUILTIN)
SRCS			+= $(MEMORY)
OBJ 			= $(patsubst %.c, $(OBJ_PATH)%.o, $(SRCS))
OBJ_BUILTIN		= $(patsubst %.c, $(OBJ_PATH)%.o, $(BUILTIN))
OBJ_MEMORY		= $(patsubst %.c, $(OBJ_PATH)%.o, $(MEMORY))

all : $(NAME)

$(NAME): $(OBJ) $(LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -I . -o $(NAME) $(LINK)

$(OBJ_PATH)%.o : $(BUILTIN_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o : $(MEMORY_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o : %.c $(OBJ_BUILTIN) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o : %.c $(OBJ_MEMORY) $(HEADERS)
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

NAME = libft.a

SRCC =  ft_atoi.c ft_calloc.c ft_bzero.c\
ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
ft_strlcat.c ft_strlcpy.c ft_strjoin.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strlen.c

OBJ = $(addprefix $(OBJ_DIR), $(SRCC:.c=.o))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB_DIR = ../
OBJ_DIR = OBJ/

all : $(LIB_DIR)$(NAME)

$(OBJ_DIR)%.o : %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)$(NAME) : $(OBJ)
	ar crs $(LIB_DIR)$(NAME) $(addprefix $(OBJ_DIR),$(notdir $(OBJ)))

re : fclean $(LIB_DIR)$(NAME)

fclean : clean
	rm -f $(LIB_DIR)$(NAME)
	rm -rf lib/libft.a
	make fclean -C $(LIB_DIR)Libft/

clean :
	rm -f $(OBJ_DIR)*.o

.PHONY: all re fclean clean
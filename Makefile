S = src/
O = obj/
I = ./
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIB = -L$(LIBFT_PATH) -lft
INC = -I$(LIBFT_PATH) -I$I

SRC = \
	$Sminishell.c \
	$Sdata_utils.c \
	$Sdata_format.c \
	$Scmds.c \
	$Sexec.c \
	$Senv_utils.c \
	$Sexp_utils.c \
	$Spipe_utils.c \
	$Sredir_utils.c

OBJ = $(SRC:$S%.c=$O%.o)

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMDIR = rmdir

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$O:
	mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJ)
	$(RMDIR) $O

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

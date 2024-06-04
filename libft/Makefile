# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rilliano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 15:44:22 by rilliano          #+#    #+#              #
#    Updated: 2023/11/11 20:02:45 by rilliano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = ./

SRC = \
	$Sft_isalpha.c \
	$Sft_isdigit.c \
	$Sft_isalnum.c \
	$Sft_isascii.c \
	$Sft_isprint.c \
	$Sft_strlen.c \
	$Sft_memset.c \
	$Sft_bzero.c \
	$Sft_memcpy.c \
	$Sft_memmove.c \
	$Sft_strlcpy.c \
	$Sft_strlcat.c \
	$Sft_toupper.c \
	$Sft_tolower.c \
	$Sft_strchr.c \
	$Sft_strrchr.c \
	$Sft_strncmp.c \
	$Sft_memchr.c \
	$Sft_memcmp.c \
	$Sft_strnstr.c \
	$Sft_atoi.c \
	$Sft_calloc.c \
	$Sft_strdup.c \
	$Sft_substr.c \
	$Sft_strjoin.c \
	$Sft_strtrim.c \
	$Sft_split.c \
	$Sft_itoa.c \
	$Sft_strmapi.c \
	$Sft_striteri.c \
	$Sft_putchar_fd.c \
	$Sft_putstr_fd.c \
	$Sft_putendl_fd.c \
	$Sft_putnbr_fd.c \
	$Sft_lstnew.c \
	$Sft_lstadd_front.c \
	$Sft_lstsize.c \
	$Sft_lstlast.c \
	$Sft_lstadd_back.c \
	$Sft_lstdelone.c \
	$Sft_lstclear.c \
	$Sft_lstiter.c \
	$Sft_lstmap.c \
	$Sget_next_line.c \
	$Sget_next_line_utils.c

OBJ = $(SRC:$S%.c=$O%.o)

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
RMDIR = rmdir

all: $(NAME)

$O:
	mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) -I$I -c $^ -o $@

$(NAME): $(OBJ)
	$(AR) $@ $^

clean:
	$(RM) $(OBJ)
	$(RMDIR) $O

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


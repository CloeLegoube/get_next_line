# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 13:00:18 by clegoube          #+#    #+#              #
#    Updated: 2016/11/17 13:33:33 by clegoube         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
OBJ =	ft_putchar.o \
		ft_putchar_fd.o \
		ft_putstr.o \
		ft_putstr_fd.o \
		ft_putendl.o \
		ft_putendl_fd.o \
		ft_putnbr.o \
		ft_putnbr_fd.o \
		ft_itoa.o \
		ft_strlen.o \
		ft_atoi.o \
		ft_strstr.o \
		ft_strnstr.o \
		ft_strcmp.o \
		ft_strncmp.o \
		ft_strdup.o \
		ft_strcpy.o \
		ft_strncpy.o \
		ft_strcat.o \
		ft_strncat.o \
		ft_strlcat.o \
		ft_strchr.o \
		ft_strrchr.o \
		ft_isalpha.o \
		ft_isdigit.o \
		ft_isalnum.o \
		ft_isascii.o \
		ft_isprint.o \
		ft_toupper.o \
		ft_tolower.o \
		ft_memset.o \
		ft_bzero.o \
		ft_memcpy.o \
		ft_memccpy.o \
		ft_memmove.o \
		ft_memchr.o \
		ft_memcmp.o \
		ft_memalloc.o \
		ft_memdel.o \
		ft_strnew.o \
		ft_strdel.o \
		ft_strclr.o \
		ft_striter.o \
		ft_striteri.o \
		ft_strmap.o \
		ft_strmapi.o \
		ft_strequ.o \
		ft_strnequ.o \
		ft_strsub.o \
		ft_strjoin.o \
		ft_strtrim.o \
		ft_strsplit.o \
		ft_lstnew.o \
		ft_lstdelone.o \
		ft_lstdel.o \
		ft_lstadd.o \
		ft_lstiter.o \
		ft_lstmap.o \
		ft_print_words_tables.o \
		ft_strsplitwhitespaces.o \
		ft_concat_params.o \
		ft_swap.o \
		ft_str_is_lowercase.o \
		ft_str_is_uppercase.o

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ) && ranlib libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean

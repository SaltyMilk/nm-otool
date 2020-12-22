# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 19:41:09 by sel-melc          #+#    #+#              #
#    Updated: 2019/11/18 15:58:03 by sel-melc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MSRC = otool.c parse_header.c parse_macho.c utils.c parse_header64.c parse_macho64.c fat.c ar.c
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
MOBJ = $(MSRC:.c=.o)

all : ft_otool

ft_otool : $(MOBJ)
	make -C libft
	$(CC) -fsanitize=address $(NAME) $(MOBJ) libft/libft.a -o ft_otool

%.o: %.c
	$(CC) $(CFLAGS) $?

clean : 
	rm -f $(MOBJ) libft/*.o
fclean :
	rm -f $(MOBJ) otool libft/libft.a libft/*o

re : fclean all

.PHONY : clean fclean re all

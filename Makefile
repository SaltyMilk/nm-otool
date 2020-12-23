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

OSRC = otool_srcs/otool.c otool_srcs/parse_header.c otool_srcs/parse_macho.c\
	otool_srcs/utils.c otool_srcs/parse_header64.c otool_srcs/parse_macho64.c\
	otool_srcs/fat.c otool_srcs/ar.c otool_srcs/print.c
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
OOBJ = $(OSRC:.c=.o)

all : ft_otool

ft_otool : $(OOBJ)
	make -C libft
	$(CC) -fsanitize=address $(NAME) $(OOBJ) libft/libft.a -o ft_otool

%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

clean : 
	rm -f $(OOBJ) libft/*.o
fclean :
	rm -f $(OOBJ) ft_otool libft/libft.a libft/*o

re : fclean all

.PHONY : clean fclean re all
#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oltkache <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/22 13:16:14 by oltkache          #+#    #+#              #
#    Updated: 2018/04/20 21:04:00 by oltkache         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ssl

SRC = main.c base64_1.c base64_2.c extra.c des1.c des1_1.c des2.c des2_1.c \
	des3.c des3_1.c des4.c des4_1.c des5.c des5_1.c des6.c des6_1.c des7.c \
	extra1.c

OBJ = main.o base64_1.o base64_2.o extra.o des1.o des1_1.o des2.o des2_1.o \
	des3.o des3_1.o des4.o des4_1.o des5.o des5_1.o des6.o des6_1.o des7.o \
	extra1.o

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o : %.c
	gcc $(FLAGS) -c $<
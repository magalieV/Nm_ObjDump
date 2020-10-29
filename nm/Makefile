##
## EPITECH PROJECT, 2018
## make file
## File description:
## make file
##

CC		=		gcc

SRCS	=	src/main.c	\
			src/get_symbol.c	\
			src/get_type.c		\
			src/get_info_type.c	\
			src/compare.c

OBJS	=		$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -fPIC -I./inc -I./../lib/

NAME	=	my_nm

$(NAME):	$(OBJS)
		make -C ../lib
		$(CC) -o $(NAME) $(OBJS) -I./inc -I./../lib/ -L. -lmy
	    cp $(NAME) ../


all:		$(NAME)

clean:
		rm -rf $(OBJS)
		make clean -C ../lib

fclean:		clean
		rm -rf $(NAME)
		make fclean -C ../lib
		rm -rf libmy.a

re:		fclean all

.PHONY:	all clean fclean re

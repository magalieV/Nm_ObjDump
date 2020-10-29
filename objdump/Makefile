##
## EPITECH PROJECT, 2018
## make file
## File description:
## make file
##

CC		=		gcc

SRCS	=	src/main.c	\
			src/display.c	\
			src/display_info.c	\
			src/get_section.c	\
			src/get_info_section.c

OBJS	=		$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -fPIC -I./inc -I./../lib/

NAME	=	my_objdump

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
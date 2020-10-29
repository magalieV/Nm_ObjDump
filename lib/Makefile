##
## EPITECH PROJECT, 2019
## make file
## File description:
## make file
##

RM		=	rm -f

SRC		=	file.c		\
			linked_list_create.c	\
			linked_list_free.c		\
			security_file.c			\

OBJ		=	$(SRC:.c=.o)


NAME	=	libmy.a

all:		$(NAME)

$(NAME):	$(OBJ)
	ar -rc $(NAME) $(OBJ)
	cp libmy.a ../nm/libmy.a
	cp libmy.a ../objdump/libmy.a
	cp libmy.a ../

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
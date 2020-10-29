##
## EPITECH PROJECT, 2019
## make file
## File description:
## make file
##

all:
	make nm
	make objdump

nm:
	make -C nm

objdump:
	make -C objdump

clean:
		make clean -C nm
		make clean -C objdump

fclean:
		make fclean -C nm
		make fclean -C objdump
		rm -rf my_objdump
		rm -rf my_nm
		rm -rf libmy.a

re:		fclean all

.PHONY	: all clean fclean re nm objdump
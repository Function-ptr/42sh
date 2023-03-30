##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRCS	=	*.c

CFLAGS	=	-Wall


all:	lib

lib:
	@gcc -c $(SRCS)
	@ar rc liball.a *.o
	@cp liball.a ../
	@cp liball.a ../../
	@cp ./include/*.h ../../include
	@find . -type f,d -name "*.o" -delete

build:
	@gcc *.c $(CFLAGS) -g3

clean:
	@rm -rf *.o .idea/
	@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete
	@find . -type f,d -name "vgcore*" -delete

fclean: clean
	@find . -type f,d -name "libmy.a" -delete

re:	fclean lib

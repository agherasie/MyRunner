##
## EPITECH PROJECT, 2021
## B-MAT-100-LYN-1-1-101pong-alexandru.gherasie
## File description:
## Makefile
##

SRC	=	my_strlen.c\
		my_putchar.c\
		my_putstr.c\
		my_put_nbr.c\
		my_strcmp.c\
		my_strncpy.c\
		my_getnbr.c\
		my_revstr.c\
		nbr_analysis.c\
		base_conversions.c\
		random.c\
		my_itoa.c\
		score.c\
		my_strcpy.c\

OBJ	=	$(SRC:.c=.o)

NAME =	libmy.a
CFLAGS += -Wextra -Iinclude

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp my.h ../include/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

auteur:
	echo $(USER) > auteur

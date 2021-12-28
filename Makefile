##
## EPITECH PROJECT, 2021
## B-MAT-100-LYN-1-1-101pong-alexandru.gherasie
## File description:
## Makefile
##

SRC	=	scripts/main.c \
		scripts/game.c \
		scripts/create.c \
		scripts/player/player_control.c \
		scripts/player/player_update.c \
		scripts/player/player_movement.c \
		scripts/player/player_create.c \
		scripts/player/collision.c \
		scripts/animation.c \
		scripts/enemy.c \
		scripts/map.c \
		scripts/background.c \
		scripts/ring.c \
		scripts/update.c \
		scripts/pause.c \
		scripts/hud.c \
		scripts/text.c \
		scripts/destroy.c \
		scripts/object_collision.c \

OBJ	=	$(SRC:.c=.o)

NAME =	my_runner
CFLAGS += -Wextra -Iinclude

all: $(NAME)

$(NAME):	$(OBJ)
	make -C lib/
	gcc -o $(NAME) $(SRC) -Llib -lmy -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -Iinclude/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f vgcore.*
	make fclean -C lib/

re:	fclean all

auteur:
	echo $(USER) > auteur
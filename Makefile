##
## EPITECH PROJECT, 2021
## B-MAT-100-LYN-1-1-101pong-alexandru.gherasie
## File description:
## Makefile
##

SRC	=	src/main.c \
		src/game.c \
		src/create.c \
		src/player/player_control.c \
		src/player/player_update.c \
		src/player/player_movement.c \
		src/player/player_create.c \
		src/player/collision.c \
		src/player/player_status.c \
		src/player/player_actions.c \
		src/player/player_animations_create.c \
		src/player/player_damage.c \
		src/player/vertical_collision.c \
		src/player/horizontal_collision.c \
		src/player/player_input.c \
		src/animation.c \
		src/enemy.c \
		src/map.c \
		src/background.c \
		src/ring.c \
		src/update.c \
		src/pause.c \
		src/hud.c \
		src/text.c \
		src/destroy.c \
		src/object_collision.c \
		src/tally.c \
		src/sound.c \
		src/update_tiles.c \
		src/camera.c \
		src/init.c \
		src/create_struct.c \
		src/create_entities.c \
		src/music.c \
		src/input.c \
		src/buttons.c \
		src/character_select.c \
		src/title.c \
		src/spring.c \
		src/tile_interpretor.c\

OBJ	=	$(SRC:.c=.o)

NAME =	my_runner
CSFML = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
CFLAGS += -Wextra -Iinclude

all: $(NAME)

$(NAME):	$(OBJ)
	make -C lib/
	gcc -o $(NAME) $(SRC) -Llib -lmy $(CSFML) -Iinclude/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f vgcore.*
	make fclean -C lib/

re:	fclean all

auteur:
	echo $(USER) > auteur

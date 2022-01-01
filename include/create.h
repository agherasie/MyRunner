/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create.h
*/

#ifndef CREATE_H_
    #define CREATE_H_

game create_values(game g);
object *create_plx(object **plx);
game create_art(game g);
game create_animations_game(game g);
void create_sonic_title(game g, int height, int width);
void create_animation(animation *anim, int length, float speed, sfBool loop);
object *create_bg(int x, int y, char *filepath, int posy);
object *create_object(int pixel_size, int scale, char *filepath);
sfText *style_text(sfText *text);

#endif /* CREATE_H_ */
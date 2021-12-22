/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create.c
*/

#include "my_runner.h"

object *create_object(int pixel_size, int scale, char *filepath)
{
    object *obj = malloc(sizeof(object));
    obj->spr = sfSprite_create();
    obj->rect.left = 0;
    obj->rect.top = 0;
    obj->rect.height = pixel_size;
    obj->rect.width = pixel_size;
    obj->scale.x = scale;
    obj->scale.y = scale;
    obj->text = sfTexture_createFromFile(filepath, NULL);
    sfSprite_setScale(obj->spr, obj->scale);
    sfSprite_setTextureRect(obj->spr, obj->rect);
    sfSprite_setTexture(obj->spr, obj->text, sfFalse);
    obj->pos.x = 0;
    obj->pos.y = 0;
    return obj;
}

void create_animation(animation *anim, int length, float speed)
{
    anim->length = length;
    anim->speed = speed;
}

player create_player()
{
    player p;
    p.obj = create_object(48, 2, "art/sonic_sheet.png");
    p.speed_x = 0;
    p.speed_y = 0;
    p.running_anim = 0;
    p.direction = 1;
    p.meters_run = 0;
    p.is_grounded = sfFalse;
    p.is_jumping = sfFalse;
    p.acceleration = sfFalse;
    p.deceleration = sfFalse;
    p.is_turning = sfFalse;
    p.anim_state = IDLE;
    p.collision_y = 0;
    p.map_pos.x = 0;
    p.map_pos.y = 0;
    create_animation(&p.anim[0], 1, 0);
    create_animation(&p.anim[1], 8, FPS);
    create_animation(&p.anim[2], 4, FPS);
    create_animation(&p.anim[3], 4, FPS);
    create_animation(&p.anim[4], 3, FPS);
    return p;
}

char **create_map(char *filepath)
{
    char **map = malloc(sizeof(char *) * (W_H / 100 + 1));
    for (int i = 0; i < 6; i++) {
        map[i] = malloc(sizeof(char) * (W_W / 100 + 1));
    }
    int file = open(filepath, O_RDONLY);
    char *buffer = malloc(sizeof(char) * 1000);
    read(file, buffer, 1000);
    close(file);
    map[W_H / 100] = NULL;
    for (int i = 0; i < W_H / 100; i++) {
        for (int j = 0; j < W_W / 100; j++) {
            while (*buffer < '0' || *buffer > '9')
                buffer++;
            map[i][j] = *buffer - 48;
            buffer++;
        }
        map[i][W_W / 100] = '\0';
    }
    return map;
}

game create_game()
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    g.clock = sfClock_create();
    g.map = create_map("map1.txt");
    g.tile = create_object(50, 2, "art/tileset.png");
    return g;
}

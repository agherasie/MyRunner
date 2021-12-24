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

void create_animation(animation *anim, int length, float speed, sfBool loop)
{
    anim->length = length;
    anim->speed = speed;
    anim->loop = loop;
}

void skip_buffer(char **buffer)
{
    while (**buffer < '0' || **buffer > '9')
        *buffer += 1;
}

int count_lines(char *buffer)
{
    int count = 1;
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\n')
            count++;
    return count;
}

int count_columns(char *buffer)
{
    int count = 0;
    for (int i = 0; buffer[i] != '\n'; i++)
        count++;
    return count;
}

char **create_map(char *filepath, game *g)
{
    int file = open(filepath, O_RDONLY);
    char *buffer = malloc(sizeof(char) * 1000);
    read(file, buffer, 1000);
    close(file);
    g->height = count_lines(buffer);
    g->width = count_columns(buffer);
    char **map = malloc(sizeof(char *) * (g->height + 1));
    for (int i = 0; i < 6; i++)
        map[i] = malloc(sizeof(char) * (g->width + 1));
    map[g->height] = NULL;
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            skip_buffer(&buffer);
            map[i][j] = *buffer - 48;
            buffer++;
        }
        map[i][g->width] = '\0';
    }
    return map;
}

game create_game()
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    g.clock = sfClock_create();
    g.map = create_map("map1.txt", &g);
    g.tile = create_object(50, 2, "art/tileset.png");
    g.paused = sfFalse;
    g.camera_pan_x = 0;
    return g;
}

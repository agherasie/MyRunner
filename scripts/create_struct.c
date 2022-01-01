/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create_struct.c
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

object *create_bg(int x, int y, char *filepath, int posy)
{
    object *obj = malloc(sizeof(object));
    obj->spr = sfSprite_create();
    obj->rect.left = 0;
    obj->rect.top = 0;
    obj->rect.height = y;
    obj->rect.width = x;
    obj->text = sfTexture_createFromFile(filepath, NULL);
    sfSprite_setTextureRect(obj->spr, obj->rect);
    sfSprite_setTexture(obj->spr, obj->text, sfFalse);
    obj->pos.x = 0;
    obj->pos.y = posy;
    sfSprite_setPosition(obj->spr, obj->pos);
    sfTexture_setRepeated(obj->text, sfTrue);
    return obj;
}

sfText *style_text(sfText *text)
{
    sfText_setStyle(text, sfTextItalic);
    sfText_setCharacterSize(text, 40);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 2);
    return text;
}

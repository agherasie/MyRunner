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

void restart(game *g, player *p)
{
    for (int i = 0; i < 6; i++)
        free(g->map[i]);
    free(g->map);
    if (g->level == 1)
        g->map = create_map("data/map1.txt", g);
    if (g->level == 2)
        g->map = create_map("data/map2.txt", g);
    if (g->level == 3)
        g->map = create_map("data/map3.txt", g);
    sfMusic_stop(g->finish_music);
    sfMusic_play(g->bg_music);
    g->camera_pan_x = 0;
    destroy_entities(g);
    g->e = create_enemies((int)(g->width / 3) - 3, g->map);
    g->frame = 0;
    g->goalframe = 0;
    g->r = create_rings((g->width - 5) * 2, g->map);
    g->ring_frame = 0;
    g->rings = 0;
    g->seconds = 0;
    g->goalsign->rect.left = 0;
    sfSprite_setTextureRect(g->goalsign->spr, g->goalsign->rect);
    p->obj->pos = (sfVector2f) {100, find_free_spot(g->map, 0) * 100 + 48};
    *p = create_bools(*p);
    p->speed_y = 0;
    p->speed_x = 0;
    p->map_pos.x = 0;
    p->map_pos.y = 0;
    g->tally_speed = 5;
    g->score = 0;
    g->rings = 0;
}

game create_values(game g)
{
    g.hiscore = 0;
    get_score(&g.hiscore);
    g.level = 1;
    g.camera_pan_x = 0;
    g.camera_pan_speed = 1;
    g.ocean_frame = 0;
    g.pause_frame = 0;
    g.frame = 0;
    g.goalframe = 0;
    g.tally_speed = 5;
    g.score = 0;
    g.rings = 0;
    g.lives = 3;
    g.ring_frame = 0;
    g.select = 0;
    g.title_sonic_frame = 10;
    g.seconds = 0;
    g.paused = sfFalse;
    g.is_runner = sfFalse;
    g.is_main_menu = sfTrue;
    g.character_menu = sfFalse;
    return g;
}

object *create_plx(object **plx)
{
    int ypos = 0;
    plx[0] = create_bg(1729, 64, "art/plx/p1-0.png", 0);
    ypos += 64;
    plx[1] = create_bg(1729, 53, "art/plx/p1-1.png", ypos * 2.5f);
    ypos += 53;
    plx[2] = create_bg(1729, 40, "art/plx/p1-2.png", ypos * 2.5f);
    ypos += 40;
    plx[3] = create_bg(1024, 107, "art/plx/p1-3.png", (ypos - 3) * 2.5f);
    return *plx;
}

game create_art(game g)
{
    g.tile = create_object(50, 2, "art/tileset.png");
    *g.plx = create_plx(g.plx);
    g.goalsign = create_object(50, 2, "art/goalsigns.png");
    g.ring = create_object(50, 2, "art/misc.png");
    g.player_icon = create_object(48, 2, "art/sonic_sheet.png");
    g.title_sonic = create_bg(254, 219, "art/title_logo.png", 0);
    g.sonic_text = sfTexture_createFromFile("art/sonic_sheet.png", NULL);
    g.tails_text = sfTexture_createFromFile("art/tails_sheet.png", NULL);
    g.knux_text = sfTexture_createFromFile("art/knuckles_sheet.png", NULL);
    g.bg_music = sfMusic_createFromFile("art/sound/rooftoprun.wav");
    g.title_music = sfMusic_createFromFile("art/sound/liveandlearn.wav");
    sfMusic_setLoop(g.bg_music, sfTrue);
    sfMusic_setLoop(g.title_music, sfTrue);
    g.finish_music = sfMusic_createFromFile("art/sound/stage-clear.wav");
    g.select_sound = sfMusic_createFromFile("art/sound/select.wav");
    return g;
}

game create_animations_game(game g)
{
    create_animation(&g.ocean_anim, 4, 10, sfTrue);
    create_animation(&g.goalanim, 5, 5, sfFalse);
    create_animation(&g.ring_anim, 16, 5, sfTrue);
    return g;
}

void create_sonic_title(game g, int height, int width)
{
    sfSprite_setScale(g.title_sonic->spr, (sfVector2f) {2, 2});
    g.title_sonic->pos = (sfVector2f) {W_W / 2 - width, W_H / 2 - height};
    sfSprite_setPosition(g.title_sonic->spr, g.title_sonic->pos);
}

game create_game()
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    g.clock = sfClock_create();
    g = create_art(g);
    g = create_values(g);
    g = create_animations_game(g);
    g.map = create_map("data/map1.txt", &g);
    g.e = create_enemies((int)(g.width / 3) - 3, g.map);
    g.r = create_rings((g.width - 5) * 2, g.map);
    g.hud_font = sfFont_createFromFile("art/sonic-hud-font.ttf");
    create_sonic_title(g, 224, 320);
    g.score_text = sfText_create();
    sfText_setFont(g.score_text, g.hud_font);
    g.score_text = style_text(g.score_text);
    g.player_icon->pos = (sfVector2f) {10, W_W - 100};
    g.player_icon->rect = (sfIntRect) {48, 0, 48, 48};
    sfSprite_setPosition(g.player_icon->spr, g.player_icon->pos);
    sfSprite_setTextureRect(g.player_icon->spr, g.player_icon->rect);
    return g;
}

/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** init.c
*/

#include "my_runner.h"
#include "create.h"

game init_to_zero(game g)
{
    g.score = 0;
    g.rings = 0;
    g.level = 0;
    g.act = 0;
    g.camera_pan = (sfVector2f) {0, 0};
    g.camera_speed = (sfVector2f) {0, 0};
    g.ocean_frame = 0;
    g.pause_frame = 0;
    g.frame = 0;
    g.goalframe = 0;
    g.hiscore = 0;
    g.ring_frame = 0;
    g.select = 0;
    g.seconds = 0;
    return g;
}

game create_values(game g)
{
    g = init_to_zero(g);
    get_score(&g.hiscore);
    g.tally_speed = 5;
    g.lives = 3;
    g.title_sonic_frame = 10;
    g.paused = sfFalse;
    g.is_runner = sfFalse;
    g.is_main_menu = sfTrue;
    g.character_menu = sfFalse;
    g.debug = sfFalse;
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
    plx[4] = create_bg(638, 223, "art/plx/p2-1.png", 0);
    plx[5] = create_bg(638, 223, "art/plx/p2-2.png", 0);
    ypos = 140;
    plx[6] = create_bg(638, 100, "art/plx/p2-3.png", ypos * 2.5f);
    plx[7] = create_bg(1000, 177, "art/plx/p3-0.png", 0);
    ypos = 100;
    plx[8] = create_bg(1000, 55, "art/plx/p3-1.png", ypos * 2.5f);
    ypos += 55;
    plx[9] = create_bg(1000, 96, "art/plx/p3-2.png", ypos * 2.5f);
    ypos += 50;
    plx[10] = create_bg(1000, 80, "art/plx/p3-3.png", (ypos) * 2.5f);
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
    g = create_music(g);
    return g;
}

game create_animations_game(game g)
{
    create_animation(&g.ocean_anim, 4, 10, sfTrue);
    create_animation(&g.goalanim, 5, 5, sfFalse);
    create_animation(&g.ring_anim, 16, 5, sfTrue);
    return g;
}

/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create_player.c
*/

#include "my_runner.h"

player create_animations(player p, char character)
{
    p.anim_frame = 0;
    p.running_anim = 0;
    p.anim_state = IDLE;
    p.character = character;
    switch (character) {
        case 's':
            return create_sonic_animations(p);
            break;
        case 't':
            return create_tails_animations(p);
            break;
        case 'k':
            return create_knux_animations(p);
            break;
    }
}

player create_bools(player p)
{
    p.is_grounded = sfFalse;
    p.is_jumping = sfFalse;
    p.acceleration = sfFalse;
    p.deceleration = sfFalse;
    p.is_turning = sfFalse;
    p.can_move = sfTrue;
    p.is_crouching = sfFalse;
    p.is_looking = sfFalse;
    p.goal_reached = sfFalse;
    p.is_hurt = sfFalse;
    p.is_spinning = sfFalse;
    p.is_dashing = sfFalse;
    p.is_charging = sfFalse;
    p.is_speeding = sfFalse;
    p.is_dropping = sfFalse;
    p.is_dying = sfFalse;
    p.is_flying = sfFalse;
    p.is_gliding = sfFalse;
    p.is_climbing = sfFalse;
    return p;
}

player create_sounds(player p)
{
    p.sound[0] = sfMusic_createFromFile("art/sound/jump.wav");
    p.sound[1] = sfMusic_createFromFile("art/sound/badnik-death.wav");
    p.sound[2] = sfMusic_createFromFile("art/sound/brake.wav");
    p.sound[3] = sfMusic_createFromFile("art/sound/death.wav");
    p.sound[4] = sfMusic_createFromFile("art/sound/spin.wav");
    p.sound[5] = sfMusic_createFromFile("art/sound/ring-loss.wav");
    p.sound[6] = sfMusic_createFromFile("art/sound/ring-collect.wav");
    p.sound[7] = sfMusic_createFromFile("art/sound/sign-post.wav");
    p.sound[8] = sfMusic_createFromFile("art/sound/tally.wav");
    p.sound[9] = sfMusic_createFromFile("art/sound/1-up.wav");
    p.sound[10] = sfMusic_createFromFile("art/sound/spring.wav");
    return p;
}

player create_player(game *g)
{
    player p;
    p.obj = create_object(48, 2, "art/sonic_sheet.png");
    p.obj->pos = (sfVector2f) {100, find_free_spot(g->map, 0) * 100 + 48};
    p.direction = 1;
    p.speed = (sfVector2f) {0, 0};
    p.collision = (sfVector2f) {0, 0};
    p.map_pos = (sfVector2i) {0, 0};
    p.is_edging = 0;
    p.cooldown = 0;
    p = create_bools(p);
    p = create_animations(p, 's');
    p = create_sounds(p);
    for (int i = 0; i < 7; i++)
        sfMusic_setVolume(p.sound[i], 50);
    sfMusic_setVolume(p.sound[JUMP], 10);
    sfMusic_setVolume(p.sound[DEATH], 100);
    return p;
}

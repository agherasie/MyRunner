/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create_player.c
*/

#include "my_runner.h"

player create_tails_animations(player p)
{
    p.anim_frame = 0;
    p.running_anim = 0;
    p.anim_state = IDLE;
    create_animation(&p.anim[IDLE], 4, 15, sfTrue);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 6, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 4, 3, sfTrue);
    create_animation(&p.anim[TURNING], 2, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 4, 5, sfTrue);
    create_animation(&p.anim[BEDGING], 4, 5, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 1, 1, sfFalse);
    create_animation(&p.anim[THUMBSUP], 8, 8, sfFalse);
    create_animation(&p.anim[HURTING], 4, 7, sfFalse);
    create_animation(&p.anim[SPINNING], 3, 5, sfTrue);
    create_animation(&p.anim[DASHING], 3, 3, sfTrue);
    create_animation(&p.anim[SPEEDING], 2, 3, sfTrue);
    create_animation(&p.anim[DYING], 3, 10, sfFalse);
    return p;
}

player create_animations(player p)
{
    p.anim_frame = 0;
    p.running_anim = 0;
    p.anim_state = IDLE;
    create_animation(&p.anim[IDLE], 1, 1, sfTrue);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 4, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 8, 3, sfTrue);
    create_animation(&p.anim[TURNING], 3, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[BEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 2, 10, sfFalse);
    create_animation(&p.anim[THUMBSUP], 13, 8, sfFalse);
    create_animation(&p.anim[HURTING], 8, 7, sfFalse);
    create_animation(&p.anim[SPINNING], 6, 5, sfTrue);
    create_animation(&p.anim[DASHING], 8, 3, sfTrue);
    create_animation(&p.anim[SPEEDING], 4, 3, sfTrue);
    create_animation(&p.anim[DYING], 4, 10, sfFalse);
    return p;
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
    return p;
}

player create_player(game *g)
{
    player p;
    p.obj = create_object(48, 2, "art/sonic_sheet.png");
    p.obj->pos = (sfVector2f) {100, find_free_spot(g->map, 0) * 100 + 48};
    p.speed_x = 0;
    p.speed_y = 0;
    p.direction = 1;
    p.meters_run = 0;
    p.collision_y = 0;
    p.collision_x = 0;
    p.map_pos.x = 0;
    p.map_pos.y = 0;
    p.is_edging = 0;
    p.cooldown = 0;
    p = create_bools(p);
    p = create_animations(p);
    p = create_sounds(p);
    for (int i = 0; i < 7; i++)
        sfMusic_setVolume(p.sound[i], 50);
    sfMusic_setVolume(p.sound[JUMP], 10);
    sfMusic_setVolume(p.sound[DEATH], 100);
    return p;
}

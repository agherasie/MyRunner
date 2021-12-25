/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create_player.c
*/

#include "my_runner.h"

player create_animations(player p)
{
    p.anim_frame = 0;
    p.running_anim = 0;
    p.anim_state = IDLE;
    create_animation(&p.anim[IDLE], 1, 1, sfTrue);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 4, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 4, 10, sfTrue);
    create_animation(&p.anim[TURNING], 3, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[BEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 2, 10, sfFalse);
    create_animation(&p.anim[THUMBSUP], 4, 10, sfFalse);
    create_animation(&p.anim[HURTING], 8, 7, sfFalse);
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
    return p;
}

player create_player()
{
    player p;
    p.obj = create_object(48, 2, "art/sonic_sheet.png");
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
    p.jump_sound = sfMusic_createFromFile("art/jump.wav");
    sfMusic_setVolume(p.jump_sound, 10);
    return p;
}

/*
** EPITECH PROJECT, 2021
** RUNNER
** File description:
** main.c
*/

#include "my_runner.h"

#define W_W 800
#define W_H 600
#define FPS 60

typedef struct sprite {
    sfSprite *spr;
    sfTexture *text;
    sfIntRect rect;
    sfVector2f scale;
    sfVector2f pos;
    float speed_x, speed_y;
    sfBool deceleration;
    int running_anim;
    int anim_frame;
    int direction;
} sprite;

void keyboard_events(game *g, sprite *p)
{
    while (sfRenderWindow_pollEvent(g->window, &g->event)) {
        if (g->event.type == sfEvtClosed)
            sfRenderWindow_close(g->window);
        if (g->event.type == sfEvtKeyPressed) {
            if (g->event.key.code == sfKeyRight) {
                p->deceleration = sfFalse;
                if (p->direction < 0)
                    p->speed_x = 0;
                p->speed_x += 0.2f;
                if (p->speed_x >= 6)
                    p->speed_x = 6;
                if (p->direction < 0) {
                    p->direction = 1;
                    p->scale.x *= -1;
                    p->pos.x -= p->rect.width * 2;
                }
            }
            if (g->event.key.code == sfKeyLeft) {
                p->deceleration = sfFalse;
                if (p->direction > 0)
                    p->speed_x = 0;
                p->speed_x += 0.2f;
                if (p->speed_x >= 6)
                    p->speed_x = 6;
                if (p->direction > 0) {
                    p->direction = -1;
                    p->scale.x *= -1;
                    p->pos.x += p->rect.width * 2;
                }
            }
        }
        if (g->event.type == sfEvtKeyReleased) {
            if (g->event.key.code == sfKeyRight || g->event.key.code == sfKeyLeft) {
                p->deceleration = sfTrue;
            }
        }
    }
}

sprite create_player()
{
    sprite player;
    player.spr = sfSprite_create();
    player.rect.left = 0;
    player.rect.top = 0;
    player.rect.height = 48;
    player.rect.width = 48;
    player.scale.x = 2;
    player.scale.y = 2;
    player.text = sfTexture_createFromFile("sonic_sheet.png", NULL);
    sfSprite_setTexture(player.spr, player.text, sfFalse);
    player.speed_x = 0;
    player.speed_y = 0;
    player.pos.x = 0;
    player.pos.y = 0;
    player.running_anim = 0;
    player.direction = 1;
    return player;
}

void anim_player(sprite *p)
{
    p->anim_frame++;
    if (p->speed_x != 0) {
        if (p->anim_frame % 10 == 0)
            p->running_anim++;
        if ((p->running_anim > 5 && p->speed_x < 6) || (p->running_anim > 3 && p->speed_x >= 6))
            p->running_anim = 0;
    }
    if (p->speed_x == 0) {
        p->running_anim = 0;
        p->rect.left = 0;
        p->rect.top = 0;
        p->rect.height = 48;
        p->rect.width = 48;
    }
    if ((p->speed_x < 6 || p->speed_x > -6) && p->speed_x != 0) {
        p->rect.top = 48;
        p->rect.left = 48 * p->running_anim;
    }
    if (p->speed_x >= 6 || p->speed_x <= -6) {
        p->rect.top = 48 * 2;
        p->rect.left = 48 * p->running_anim;
    }
}

void update_player(sprite *p, game *g)
{
    sfSprite_setScale(p->spr, p->scale);
    if (p->pos.y < 500) {
        p->speed_y += 0.5f;
    }
    if (p->pos.y > 500) {
        p->speed_y = 0;
        p->pos.y = 500;
    }
    p->pos.x += p->speed_x * p->direction;
    p->pos.y += p->speed_y;
    if (p->deceleration == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= 0.2f;
        if (p->speed_x <= 0.2f) {
            p->speed_x = 0;
            p->deceleration = sfFalse;
        }
    }
    anim_player(p);
    printf("running_anim = %i\n", p->running_anim);
    sfSprite_setTextureRect(p->spr, p->rect);
    printf("speed_x = %f\nspeed_y = %f\n", p->speed_x, p->speed_y);
    sfSprite_setPosition(p->spr, p->pos);
    sfRenderWindow_drawSprite(g->window, p->spr, NULL);
}

void update(game *g, sprite *p)
{
    while (sfRenderWindow_isOpen(g->window)) {
        g->time = sfClock_getElapsedTime(g->clock);
        if (g->time.microseconds > 1000) {
            sfClock_restart(g->clock);
            sfRenderWindow_display(g->window);
            sfRenderWindow_clear(g->window, sfBlack);
            keyboard_events(g, p);
            update_player(p, g);
        }
    }
    return;
}

game create_game()
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    g.clock = sfClock_create();
    return g;
}

int launch_game()
{
    game g = create_game();
    sprite p = create_player();
    sfRenderWindow_setMouseCursorVisible(g.window, sfTrue);
    sfRenderWindow_setFramerateLimit(g.window, FPS);
    update(&g, &p);
    return EXIT_SUCCESS;
}

void print_file(char *filepath, int buffsize)
{
    int fp = open(filepath, O_RDONLY);
    char buff[buffsize];
    if (fp != -1) {
        read(fp, buff, buffsize);
        my_putstr(buff);
        close(fp);
    }
    return;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        return launch_game();
    } else if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0)
            print_file("readme", 1000);
        if (my_strcmp(av[1], "-c") == 0)
            print_file("credits", 2100);
    }
}

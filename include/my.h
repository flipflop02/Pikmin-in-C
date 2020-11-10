/*
** EPITECH PROJECT, 2018
** my h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Graphics/Export.h>
#include <SFML/System/Time.h>

typedef struct t_hitbox_square {
    int x;
    int y;
    int width;
    int height;
}t_hit_s;

typedef struct t_window {
    sfVideoMode mode;
    sfView *view;
    sfFloatRect size;
    int height;
    int width;
    sfRenderWindow *window;
}t_window;

typedef struct t_pikminfield {
    int place;
    int state;
    int width;
    int speed;
    sfVector2f pos_c;
    char *type;
    sfVector2f pos;
    sfVector2f scale;
    sfIntRect rect;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f relative_captain;
    t_hit_s *hitbox;
    struct t_pikminfield *next;
    struct t_pikminfield *prev;
}t_pikminfield;

typedef struct t_character {
    sfSprite *sprite;
    sfTexture *texture_front;
    sfTexture *texture_back;
    sfTexture *texture_left;
    sfTexture *texture_right;
    t_hit_s *hitbox;
    sfIntRect rect;
    sfVector2f scale;
    sfVector2f pos;
    int width;
    int up;
    int down;
    int left;
    int right;
    sfVector2f point;
}t_character;

typedef struct t_entity {
    t_pikminfield *pkmn_field;
    t_character *olimar;
}t_entity;

typedef struct t_game {
    t_window *win;
    t_entity *en;
    sfEvent event;
}t_game;

int world(t_game *game);
void handle_pikmin_hitbox(t_pikminfield *pikmin);

#endif

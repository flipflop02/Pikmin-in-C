/*
** Pikmin C project
** 
**
**  position dynamique à faire
*/

#include "../../include/my.h"

void draw_pikmin(sfRenderWindow *window, t_pikminfield *pkmn_field, int i) {
    t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") != 0) {
            if (pkmn_field->pos.y + pkmn_field->width == i) {
                sfRenderWindow_drawSprite(window, pkmn_field->sprite, NULL);
            }
        }
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") != 0)) {
        if (pkmn_field->pos.y + pkmn_field->width == i)
            sfRenderWindow_drawSprite(window, pkmn_field->sprite, NULL);
    }
    pkmn_field = &begin;
}

sfVector2f getDistanceFromCaptain(t_character *chara, t_pikminfield *pikmin) {
    sfVector2f res;
    int i = 0;
    int j = 0;
    for (; pikmin->pos.x + i < chara->pos.x + 30; i++);
    for (; pikmin->pos.y + j < chara->pos.y + 30; j++);
    res.x = i;
    res.y = j;
    return (res);
}

void following(t_character *chara, t_pikminfield *pikmin) {
    sfVector2f dist;
    int i = 0;
    int j = 0;
    for (; (pikmin->pos.x + 7 + pikmin->relative_captain.x) + i < chara->point.x; i++);
    for (; (pikmin->pos.y + 24 + pikmin->relative_captain.y) + j < chara->point.y; j++);
    for (; (pikmin->pos.x + 7 + pikmin->relative_captain.x) + i > chara->point.x; i--);
    for (; (pikmin->pos.y + 24 + pikmin->relative_captain.y) + j > chara->point.y; j--);
    if (i > 0)
        pikmin->pos.x = pikmin->pos.x + pikmin->speed;
    if (i < 0)
        pikmin->pos.x = pikmin->pos.x - pikmin->speed;
    if (j > 0)
        pikmin->pos.y = pikmin->pos.y + pikmin->speed;
    if (j < 0)
        pikmin->pos.y = pikmin->pos.y - pikmin->speed;
    sfSprite_setPosition(pikmin->sprite, pikmin->pos);
}

void handle_state(t_game *game, t_pikminfield *pkmn_field) {
        t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (pkmn_field->state == 1) {
            handle_pikmin_hitbox(pkmn_field);
            following(game->en->olimar, pkmn_field);
        }
    }
    if ((pkmn_field->next == NULL)) {
        if (pkmn_field->state == 1) {
            handle_pikmin_hitbox(pkmn_field);
            following(game->en->olimar, pkmn_field);
        }
            
    }
    pkmn_field = &begin;
}

t_pikminfield *add_new_pikmin(t_pikminfield *pkmn_field, char *type) {
    t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") == 0) {
            pkmn_field->type = strdup(type);
            pkmn_field->state = 1;
            pkmn_field->speed = 1;
            printf("Added %d pikmin %d\n", pkmn_field->place, pkmn_field->speed);
            break;
        }
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") == 0)) {
        pkmn_field->type = strdup(type);
        pkmn_field->state = 1;
        pkmn_field->speed = 1;
        printf("Added %d pikmin\n", pkmn_field->place);
    }
    pkmn_field = &begin;
    return (pkmn_field);
}

t_character *handle_character_movement(t_character *character){

    // character->point.x = ((15 * character->scale.x) + character->pos.x);
    // character->point.y = ((49 * character->scale.y) + character->pos.y - 50);
    if (character->up == 1) {
        sfSprite_setTexture(character->sprite, character->texture_back, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y = character->pos.y - 2;
        character->point.x = ((15 * character->scale.x) + character->pos.x + 125);
        character->point.y = ((49 * character->scale.y) + character->pos.y + 30 + 250);
    }
    if (character->down == 1) {
        sfSprite_setTexture(character->sprite, character->texture_front, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y = character->pos.y + 2;
        character->point.x = ((15 * character->scale.x) + character->pos.x + 125);
        character->point.y = ((49 * character->scale.y) + character->pos.y - 30);
    }
    if (character->left == 1) {
        sfSprite_setTexture(character->sprite, character->texture_left, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x = character->pos.x - 2;
        character->point.x = ((15 * character->scale.x) + character->pos.x + 30 + 250);
        character->point.y = ((49 * character->scale.y) + character->pos.y + 125);
    }
    if (character->right == 1) {
        sfSprite_setTexture(character->sprite, character->texture_right, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x = character->pos.x + 2;
        character->point.x = ((15 * character->scale.x) + character->pos.x - 30);
        character->point.y = ((49 * character->scale.y) + character->pos.y + 125);
    }
    printf("%f %f\n", character->point.x, character->point.y);
    sfSprite_setPosition(character->sprite, character->pos);
    return (character);
}

int world_event(t_game *game) {
    while (sfRenderWindow_pollEvent(game->win->window, &game->event)){
        if (game->event.type == sfEvtClosed)
            sfRenderWindow_close(game->win->window);
        if (game->event.type == sfEvtKeyPressed) {
            if (sfKeyboard_isKeyPressed(sfKeyP))
                add_new_pikmin(game->en->pkmn_field, "red");
        }

        if (sfKeyboard_isKeyPressed(sfKeyZ))
            game->en->olimar->up = 1;
        else
            game->en->olimar->up = 0;
        if (sfKeyboard_isKeyPressed(sfKeyS))
            game->en->olimar->down = 1;
        else
            game->en->olimar->down = 0;
        if (sfKeyboard_isKeyPressed(sfKeyQ))
            game->en->olimar->left = 1;
        else
            game->en->olimar->left = 0;
        if (sfKeyboard_isKeyPressed(sfKeyD))
            game->en->olimar->right = 1;
        else
            game->en->olimar->right = 0;
        sfSprite_setPosition(game->en->olimar->sprite, game->en->olimar->pos);

    }
}

int draw_character(sfRenderWindow *window, t_character *olimar)
{
    sfRenderWindow_drawSprite(window, olimar->sprite, NULL);
}

void handle_chara_hitbox(t_character *chara)
{
    chara->hitbox->x = chara->pos.x + 2;
    chara->hitbox->y = chara->pos.y + 45;
    chara->hitbox->height = 13 * chara->scale.x;
    chara->hitbox->width = 14 * chara->scale.y;
}

void handle_pikmin_hitbox(t_pikminfield *pikmin)
{
    pikmin->hitbox->x = pikmin->pos.x + 4;
    pikmin->hitbox->y = pikmin->pos.y + 25;
    pikmin->hitbox->height = 7 * pikmin->scale.x;
    pikmin->hitbox->width = 11 * pikmin->scale.y;
}

void draw_screen_3d(sfRenderWindow *window, t_entity *entity, int width) {
    for (int j = 0; j <= width; j++) {
        if (j == ((int)entity->olimar->pos.y + entity->olimar->width)) {
            draw_character(window, entity->olimar);
        }
        draw_pikmin(window, entity->pkmn_field, j);
    }
}

void draw_shadow(sfRenderWindow *window, t_character *character, t_pikminfield *pkmn_field)
{
    t_pikminfield begin = *(pkmn_field);
    sfRenderWindow_drawSprite(window, character->shadow->sprite, NULL);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") != 0) {
            sfRenderWindow_drawSprite(window, pkmn_field->shadow->sprite, NULL);
        }
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") != 0)) {
        sfRenderWindow_drawSprite(window, pkmn_field->shadow->sprite, NULL);
    }
    pkmn_field = &begin;
}

void handle_shadow_pos(t_character *chara, t_pikminfield *pkmn_field)
{
    t_pikminfield begin = *(pkmn_field);
    chara->shadow->pos.x = chara->pos.x;
    chara->shadow->pos.y = chara->pos.y + 74;
    sfSprite_setPosition(chara->shadow->sprite, chara->shadow->pos);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") != 0) {
            pkmn_field->shadow->pos.x = pkmn_field->pos.x - 8;
            pkmn_field->shadow->pos.y = pkmn_field->pos.y + 30;
            sfSprite_setPosition(pkmn_field->shadow->sprite, pkmn_field->shadow->pos);
        }
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") != 0)) {
        pkmn_field->shadow->pos.x = pkmn_field->pos.x - 8;
        pkmn_field->shadow->pos.y = pkmn_field->pos.y + 30;
        sfSprite_setPosition(pkmn_field->shadow->sprite, pkmn_field->shadow->pos);
    }
    pkmn_field = &begin;
}

int world(t_game *game)
{
    world_event(game);
    handle_character_movement(game->en->olimar);
    handle_state(game, game->en->pkmn_field);
    handle_chara_hitbox(game->en->olimar);
    handle_shadow_pos(game->en->olimar, game->en->pkmn_field);
    //printf("[Hitbox | x : %d | y : %d | h : %d | w : %d]\n", game->en->olimar->hitbox->x, game->en->olimar->hitbox->y, game->en->olimar->hitbox->height, game->en->olimar->hitbox->width);
    draw_shadow(game->win->window, game->en->olimar, game->en->pkmn_field);
    draw_screen_3d(game->win->window, game->en, game->win->width);
}

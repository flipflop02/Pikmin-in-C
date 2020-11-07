/*
** Pikmin C project 
*/

#include "include/my.h"

t_pikminfield *new_node_pf(t_pikminfield *list, int count)
{
    t_pikminfield *new = malloc(sizeof(t_pikminfield));
    new->place = count;
    if (list == NULL){
        new->next = NULL;
        new->prev = NULL;
    } else {
        new->next = list;
        list->prev = new;
    }
    return (new);
}

t_pikminfield *generate_pikmin_field(t_pikminfield *pkmn_field, int count)
{
    for (int i = 1; i <= count; i++)
        pkmn_field = new_node_pf(pkmn_field, i);

    for (;pkmn_field->next != NULL; pkmn_field = pkmn_field->next);
    return (pkmn_field);
}

t_game *init_struct(t_game *game) {
    game = malloc(sizeof(t_game));
    game->win = malloc(sizeof(t_window));
    game->en = malloc(sizeof(t_entity));
    game->en->olimar = malloc(sizeof(t_character));
    game->en->pkmn_field = NULL;
    game->en->pkmn_field = generate_pikmin_field(game->en->pkmn_field, 100);

    for (;  game->en->pkmn_field->prev != NULL ;  game->en->pkmn_field = game->en->pkmn_field->prev)
        printf("[%d]", game->en->pkmn_field->place);
    printf("[%d]\n", game->en->pkmn_field->place);
    return (game);
}

t_window *init_window(t_window *win) {
    win->length = 1280;
    win->width = 720;
    win->mode = (sfVideoMode){win->length, win->width, 32};
    win->window = sfRenderWindow_create(win->mode, "Pikmin C", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(win->window, 60);
    return (win);
}

t_entity *init_entity(t_entity *en) {
}

t_game *global_init(t_game *game) {
    game = init_struct(game);
    game->win = init_window(game->win);
    game->en = init_entity(game->en);
    return (game);
}

int event(t_game *game) {
    while (sfRenderWindow_pollEvent(game->win->window, &game->event)){
        if (game->event.type == sfEvtClosed)
            sfRenderWindow_close(game->win->window);
    }
}

int game_loop(t_game *game) {
      while (sfRenderWindow_isOpen(game->win->window)) {
        event(game);
        sfRenderWindow_clear(game->win->window, sfBlack);
        sfRenderWindow_display(game->win->window);
    }
}

int main(int ac, char **av)
{
    t_game *game = global_init(game);
    game_loop(game);
    return (0);
}

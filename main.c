/*
** Pikmin C project 
*/

#include "include/my.h"

t_pikminfield *new_node_pf(t_pikminfield *list, int count)
{
    t_pikminfield *new = malloc(sizeof(t_pikminfield));
    new->hitbox = malloc(sizeof(t_hit_s));
    new->hitbox->x = 0;
    new->hitbox->y = 0;
    new->hitbox->width = 0;
    new->hitbox->height = 0;                       
    new->place = count;
    new->type = strdup("NONE");
    new->state = 0;
    new->width = 43;
    new->speed = 0;
    new->texture = sfTexture_createFromFile("ressources/textures/red/test.png", NULL);
    new->pos.x = 0;
    new->pos.y = 0;
    new->relative_captain.x = (((count-1)/10) * 25);
    new->relative_captain.y = (((count-1)%10) * 25);
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    if (list == NULL){
        printf("list is null\n");
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
    for (int i = 0; i < count; i++)
        pkmn_field = new_node_pf(pkmn_field, count - i);

    return (pkmn_field);
}

t_game *init_struct(t_game *game) {
    printf("- Malloc game\n");
    game = malloc(sizeof(t_game));
    printf("- Malloc window\n");
    game->win = malloc(sizeof(t_window));
    printf("- Malloc entity\n");
    game->en = malloc(sizeof(t_entity));
    printf("- Malloc entity olimar\n");
    game->en->olimar = malloc(sizeof(t_character));
    printf("- Malloc entity olimar hitboxes\n");
    game->en->olimar->hitbox = malloc(sizeof(t_hit_s));
    printf("- Mallocing pikmin field\n");
    game->en->pkmn_field = NULL;
    printf("    Generating pikmin field\n");
    game->en->pkmn_field = generate_pikmin_field(game->en->pkmn_field, 100);
    printf("    Test of the ll\n");
    printf("- Malloc done\n");
    return (game);
}

t_window *init_window(t_window *win) {
    win->height = 1280;
    win->width = 720;
    win->size.top = -100;
    win->size.left = 0;
    win->size.height = win->height;
    win->size.width = win->width;
    win->view = sfView_createFromRect(win->size);
    win->mode = (sfVideoMode){win->height, win->width, 32};
    win->window = sfRenderWindow_create(win->mode, "Pikmin C", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(win->window, 60);
    //sfRenderWindow_setView(win->window, win->view);
    return (win);
}

t_character *init_character (t_character *chara, char *name) {
    chara->texture_front = sfTexture_createFromFile("ressources/textures/olimar/olimar_front.png", NULL);
    chara->texture_back = sfTexture_createFromFile("ressources/textures/olimar/olimar_back.png", NULL);
    chara->texture_left = sfTexture_createFromFile("ressources/textures/olimar/olimar_left.png", NULL);
    chara->texture_right = sfTexture_createFromFile("ressources/textures/olimar/olimar_right.png", NULL);
    chara->sprite = sfSprite_create();
    chara->rect.height = 60;
    chara->rect.width = 60;
    chara->rect.top = 0;
    chara->rect.left = 0;
    chara->scale.x = 1.5;
    chara->scale.y = 1.5;
    chara->pos.x = 0;
    chara->pos.y = 0;
    chara->width = 60 * chara->scale.x;
    sfSprite_setTexture(chara->sprite, chara->texture_front, sfTrue);
    sfSprite_setTextureRect(chara->sprite, chara->rect);
    sfSprite_setScale(chara->sprite, chara->scale);
    return (chara);
}

t_entity *init_entity(t_entity *en) {
    en->olimar = init_character(en->olimar, "olimar");
    return (en);
}

t_game *global_init(t_game *game) {
    printf("*********INIT STRUCTURE************\n");
    game = init_struct(game);
    printf("*********INIT WINDOW***************\n");
    game->win = init_window(game->win);
    printf("*********INIT ENTITY***************\n");
    game->en = init_entity(game->en);
    printf("---Init done----\n");

    return (game);
}

int game_loop(t_game *game) {
      while (sfRenderWindow_isOpen(game->win->window)) {
        sfRenderWindow_clear(game->win->window, sfBlack);
        world(game);
        sfRenderWindow_display(game->win->window);
    }
}

int main(int ac, char **av)
{
    t_game *game = global_init(game);
    game_loop(game);
    return (0);
}

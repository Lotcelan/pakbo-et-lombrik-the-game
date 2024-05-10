#include "ping_pong.h"

void update_ping_pong(GameData* game) {
    (void)game;

    Rectangle* left_platform = get(game->current_scene->objects, "left_platform", strcmp);
    Rectangle* right_platform = get(game->current_scene->objects, "right_platform", strcmp);
    Circle* ball = get(game->current_scene->objects, "ball", strcmp);

    if (left_platform == NULL || right_platform == NULL || ball == NULL) {
        printf("hello c pas normal :)\n");
        return;
    }

    Box* left_coll = init_rect_box(left_platform->x, left_platform->y, left_platform->w, left_platform->h);
    Box* right_coll = init_rect_box(right_platform->x, right_platform->y, right_platform->w, right_platform->h);
    Box* ball_coll = init_rect_box(ball->x, ball->y, ball->radius*2, ball->radius*2);
    if (are_colliding(game->player->hurt_box, left_coll) || are_colliding(game->player->hurt_box, right_coll) || are_colliding(game->player->hurt_box, ball_coll)) {
        damage_entity(game, game->player, 1, 500, -1);
    }

    float* ball_x_velocity = get(game->current_scene->objects, "ball_x_velocity", strcmp);
    float* ball_y_velocity = get(game->current_scene->objects, "ball_y_velocity", strcmp);

    if (ball_x_velocity == NULL || ball_y_velocity == NULL) {
        printf("hello c pas normal :) 2\n");
        return;
    }

    int next_x = ball->x + ceil(*ball_x_velocity * game->deltaT /1000);
    Box* next_x_ball_coll = init_rect_box(next_x, ball->y, ball->radius*2, ball->radius*2);

    if (are_colliding(next_x_ball_coll, left_coll) || are_colliding(next_x_ball_coll, right_coll) || next_x < 0 || next_x > game->width_amount * CELL_WIDTH) {
        *ball_x_velocity = -*ball_x_velocity;
        next_x = ball->x + (*ball_x_velocity * game->deltaT /1000);
    }
    
    int next_y = ball->y + ceil(*ball_y_velocity * game->deltaT /1000);
    if (next_y < 0 || next_y > game->height_amount * CELL_HEIGHT) {
        *ball_y_velocity = -*ball_y_velocity;
        next_y = ball->y + ceil(*ball_y_velocity * game->deltaT /1000);
    }

    printf("next_x: %d, next_y: %d\n", next_x, next_y);
    printf("left_platform x: %d, y: %d\n", left_platform->x, left_platform->y);
    printf("right_platform x: %d, y: %d\n", right_platform->x, right_platform->y);
    printf("ball x: %d, y: %d\n", ball->x, ball->y);

    ball->x = next_x;
    ball->y = next_y;

    left_platform->y = next_y;
    right_platform->y = next_y;

    free_box(next_x_ball_coll);
    free_box(left_coll);
    free_box(right_coll);
    free_box(ball_coll);

    

    return;
}

void event_handler_ping_pong(GameData* game) {
    switch (game->event.type) {
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.sym) {
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            game->state = CLOSING;
            break;
        default:
            break;
    }
    return;
}

void populate_ping_pong(GameData* game) {
    push_background_structures(game);
    // change_entity_coordinates(game->player, 50, 10);

    // for (int i = 0; i < 1; i++) {
    //     EntityInitFunc* duck = get(game->entities, "duck_green", strcmp);
    //     Entity* e = (*duck)(game, (rand() %  16) * CELL_WIDTH, (rand() % 4) * CELL_HEIGHT);
    //     game->current_scene->entities = append_first(e, game->current_scene->entities);
    // }

    Rectangle* left_platform = init_rectangle(0,0,CELL_WIDTH/2, CELL_HEIGHT*2, (SDL_Color){0,0,0,255}, (SDL_Color){255,255,255,255});
    Rectangle* right_platform = init_rectangle((game->width_amount -1) * CELL_WIDTH + CELL_WIDTH / 2 ,0,CELL_WIDTH/2, CELL_HEIGHT*2, (SDL_Color){0,0,0,255}, (SDL_Color){255,255,255,255});
    Circle* ball = init_circle(game->width_amount / 2 * CELL_WIDTH, game->height_amount / 2 * CELL_HEIGHT, CELL_WIDTH / 4, (SDL_Color){255,255,255,255});

    float* ball_x_velocity = (float*)malloc(sizeof(float));
    float* ball_y_velocity = (float*)malloc(sizeof(float));

    *ball_x_velocity = 200; //(float)(rand() % 500) + 1000;
    *ball_y_velocity = 200; //(float)(rand() % 500) + 1000;

    insert(game->current_scene->objects, "left_platform", left_platform, free_rectangle);
    insert(game->current_scene->objects, "right_platform", right_platform, free_rectangle);
    insert(game->current_scene->objects, "ball", ball, free_circle);

    insert(game->current_scene->objects, "ball_x_velocity", ball_x_velocity, free);
    insert(game->current_scene->objects, "ball_y_velocity", ball_y_velocity, free);

    push_render_stack_circle(game, ball, false); // on ne refait pas de malloc a chaque update donc non temporaire
    push_render_stack_rect(game, left_platform, false);
    push_render_stack_rect(game, right_platform, false);
    
}

// void test(Entity* e, float delta){
//     return;
// }

Scene* init_ping_pong(GameData* game) {
    Scene* scene = init_scene(game, "ping_pong");

    // test pour l'affichage des entités
    // début tests Sacha
    // int* nbs = malloc(sizeof(int));
    // nbs[255] = 8;
    // nbs[255] = 8;
    // int* lock = malloc(sizeof(int));
    // lock[0] = 0;
    // SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_lombric_walk");
    // // Sprite* lb_sprite = init_sprite(12, spritesheet, 16, 16, nbs, lock);
    // Entity* lombric = init_entity(15, 10, 15, spritesheet, 16, 16, nbs, lock);
    // lombric->update_animation = test;
    // int* t = lombric->sprite->frames[0]->value;
    // int* cf = lombric->sprite->currentFrame->next->value;
    // printf("\n\n%d, %d\nnext frame : %d, %d\n\n", t[0], t[1], cf[0], cf[1]);
    // scene->entities = append_first(lombric, scene->entities);
    // fin tests Sacha

    scene->update = update_ping_pong;
    scene->event_handler = event_handler_ping_pong;
    scene->populate = populate_ping_pong;


    return scene;
}

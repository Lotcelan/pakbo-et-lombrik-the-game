#ifndef RESOURCES_H
#define RESOURCES_H

#include "engine/include/hashtable.h"
#include "engine/include/assets.h"
#include <string.h>

HashTable* init_resources(void);
extern unsigned char src_assets_resized_background_png[];
extern int src_assets_resized_background_png_len;

extern unsigned char src_assets_sol_png[];
extern int src_assets_sol_png_len;

extern unsigned char src_assets_plateforme_surelevee_png[];
extern int src_assets_plateforme_surelevee_png_len;

extern unsigned char src_assets_dirt_png[];
extern int src_assets_dirt_png_len;

extern unsigned char src_assets_lombric_walk_png[];
extern int src_assets_lombric_walk_png_len;

extern unsigned char src_assets_sol_eclaire_png[];
extern int src_assets_sol_eclaire_png_len;

extern unsigned char src_assets_toolbox_png[];
extern int src_assets_toolbox_png_len;

extern unsigned char src_assets_black_png[];
extern int src_assets_black_png_len;

extern unsigned char src_assets_background_png[];
extern int src_assets_background_png_len;

extern unsigned char src_assets_birck_background_png[];
extern int src_assets_birck_background_png_len;

extern unsigned char src_assets_door_png[];
extern int src_assets_door_png_len;

extern unsigned char src_assets_wall_jpg[];
extern int src_assets_wall_jpg_len;

extern unsigned char src_assets_ecocup_png[];
extern int src_assets_ecocup_png_len;

extern unsigned char src_assets_random_block_png[];
extern int src_assets_random_block_png_len;

extern unsigned char src_assets_block_circles_png[];
extern int src_assets_block_circles_png_len;

extern unsigned char src_assets_blurred_brick_background_with_floor_png[];
extern int src_assets_blurred_brick_background_with_floor_png_len;

#endif // RESOURCES_H

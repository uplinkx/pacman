/***************************************************************************
 * FILENAME:    pacman.h
 * DESCRIPTION: General header for pacman.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Feb2021
***************************************************************************/

#ifndef PACMAN_H
# define PACMAN_H

# include "SDLX.h"

# include "pacman_structs.h"
# include "pacman_assets.h"

# define ASSETS "assets/"

void	*new_scene(size_t size, t_pmContext *context, char *background_path, void *(close)(t_pmContext *, void *), void *(update)(t_pmContext *, void *));
void	*button_trigger_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length);
void	*button_trigger_start_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length);
void	catch_gesture(void);

void	change_message(t_text *text, char *to, SDL_bool allocate);
void	create_text(t_text *dst, int color, SDL_Rect loc, char *message, double scale, TTF_Font *font);
void	update_text(t_text *text, size_t size);

SDLX_iMap	*pacman_key_map(size_t *size);
SDLX_iMap	*pacman_pad_map(size_t *size);

void		instance_ghost(t_ghost *dest, int ghost, int x, int y, void (*fn)(struct s_level_scene *));
void		update_ghost(t_level_scene *scene, t_ghost *ghost);
void		realign_ghost(t_ghost *ghost);

void		target_clyde(t_level_scene *gContext);
void		target_inky(t_level_scene *gContext);
void		target_pinky(t_level_scene *gContext);
void		target_blinky(t_level_scene *gContext);
void		draw_target(int x, int y);

void		instance_player(t_pacman *player, int x, int y);
void		update_player(int ticks, t_pacman *player);
void		realign_player(t_pacman *player);

void		draw_pellets(t_map *map);
void		fill_map(t_map *map_dest);
void		update_map(t_level_scene *scene);

void	*main_menu_init(t_pmContext *context, void *vp_scene);
void	*main_menu_close(t_pmContext *context, void *vp_scene);
void	*main_menu_update(t_pmContext *context, void *vp_scene);

void	*level_init(t_pmContext *context, void *vp_scene);
void	*level_close(t_pmContext *context, void *vp_scene);
void	*level_update(t_pmContext *context, void *vp_scene);

void	*gameover_init(t_pmContext *context, void *vp_scene);
void	*gameover_close(t_pmContext *context, void *vp_scene);
void	*gameover_update(t_pmContext *context, void *vp_scene);

#endif

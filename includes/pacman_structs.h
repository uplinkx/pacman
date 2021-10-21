/***************************************************************************
 * FILENAME:    pacman_structs.h
 * DESCRIPTION: Structs to be used in the PacMan application.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Feb2021
***************************************************************************/

#include "SDLX.h"

struct s_pmContext;
struct s_level_scene;

#define GAME_COLS 29
#define GAME_ROWS 31
typedef char t_map[GAME_ROWS][GAME_COLS];

enum	ghost_state
{
	GM_NONE,
	GM_EATEN,
	GM_FRIGHTEN,
	GM_CHASE,
};

typedef struct	s_ghost
{
	int			x;
	int			y;

	int			tar_x;
	int			tar_y;

	int				mode;
	SDLX_direction	from;

	int			ghost;
	SDLX_Sprite	sprite;

	t_map		*map;

	void		(*ghost_target)(struct s_level_scene *);
}				t_ghost;

typedef struct	s_pacman
{
	int			x;
	int			y;

	int			prev_x;
	int			prev_y;

	SDLX_direction	facing;

	SDLX_Sprite		sprite;

	int			x_i;
	int			y_i;

	SDLX_direction	facing_i;

	SDLX_Sprite		sprite_i;

	t_map			*map;

	SDL_bool		dead;
}				t_pacman;

typedef void *(t_scene_fn)(struct s_pmContext *, void *);

typedef struct	s_pmContext
{
	int					ticks;
	SDLX_Sprite			background;
	SDLX_RenderQueue	rQueue;

	t_scene_fn	*init_fn;
	t_scene_fn	*update_fn;
	t_scene_fn	*close_fn;

	void		*meta;

	SDL_bool			shouldChange;
	SDL_bool			shouldQuit;


	// SDLX_Sprite	background;
	// t_map		map;

	// int				fright_ticks;
	// t_ghost			blinky;
	// t_ghost			pinky;
	// t_ghost			inky;
	// t_ghost			clyde;

	// t_pacman			player;
	// SDL_bool			pause;

	SDLX_GameInput		game_in;


}				t_pmContext;

typedef struct	s_level_scene
{
	SDLX_Sprite	background;
	t_map		map;
	int			*ticks;

	int				fright_ticks;
	t_ghost			blinky;
	t_ghost			pinky;
	t_ghost			inky;
	t_ghost			clyde;

	t_pacman			player;
	SDL_bool			pause;
	SDL_bool			clone;

}				t_level_scene;

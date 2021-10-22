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


typedef struct	s_text
{
	SDL_Color	color;
	double		scale;
	size_t		message_length;
	char		*message;
	char		*set;
	SDLX_Sprite	sprite;

	TTF_Font	*set_font;
}				t_text;

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

	t_map			*map;

	SDL_bool		dead;
}				t_pacman;

typedef void *(t_scene_fn)(struct s_pmContext *, void *);

typedef struct	s_pmContext
{
	SDLX_Sprite	background;

	t_scene_fn	*init_fn;
	t_scene_fn	*update_fn;
	t_scene_fn	*close_fn;

	void		*meta;

	SDL_bool	shouldChange;
	SDL_bool	shouldQuit;

	TTF_Font	*font;
	TTF_Font	*font2;
}				t_pmContext;

typedef struct	s_level_scene
{
	int			ticks;
	int			fright_ticks;
	t_map		map;

	t_ghost		blinky;
	t_ghost		pinky;
	t_ghost		inky;
	t_ghost		clyde;

	t_pacman	player;
	SDL_bool	pause;
	SDL_bool	clone;

	t_text		ready;

}				t_level_scene;

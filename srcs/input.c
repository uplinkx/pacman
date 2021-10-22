/***************************************************************************
 * FILENAME:    input.c
 * DESCRIPTION: Input manager and control file.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Feb2021
***************************************************************************/

#include "pacman.h"

SDLX_iMap	*pacman_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_LEFT},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_RIGHT},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_UP},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_DOWN},

		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_D},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_W},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_S},

		(SDLX_iMap){&BMAP(button_START),	1, SDL_SCANCODE_R},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}

SDLX_iMap	*pacman_pad_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_CONTROLLER_BUTTON_DPAD_UP},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_CONTROLLER_BUTTON_DPAD_DOWN},

		(SDLX_iMap){&BMAP(button_START),	1, SDL_CONTROLLER_BUTTON_START},
		(SDLX_iMap){&BMAP(button_GUIDE),	1, SDL_CONTROLLER_BUTTON_BACK},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}

void	catch_gesture(void)
{
	int		dx, dy;
	double	dist;
	double	angle;
	int		deg;

	dx = g_GameInput.GameInput.primary_delta.x;
	dy = g_GameInput.GameInput.primary_delta.y;
	dist = SDL_sqrt(dx * dx + dy * dy);

	if (dist > 40 && g_GameInput.GameInput.button_primleft)
	{
		angle = SDL_atan2(dx, dy);
		deg = SDLX_Radian_to_Degree(angle) + 360 + 45;
		deg %= 360;

		// SDL_Log("%d", deg);
		if (deg < 90)
			g_GameInput.GameInput.button_DPAD_LEFT |= 2;
		else if (deg < 180)
			g_GameInput.GameInput.button_DPAD_DOWN |= 2;
		else if (deg < 270)
			g_GameInput.GameInput.button_DPAD_RIGHT |= 2;
		else
			g_GameInput.GameInput.button_DPAD_UP |= 2;

	}
}
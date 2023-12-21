/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:38:30 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 19:03:20 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_EVENTS_H
# define KEY_EVENTS_H

# include "struct_cube.h"
# include "display.h"

# define SPEED 0.1
# define SPEED_ROT 2

typedef struct s_key_event
{
	int				rot;
	int				up;
	int				lat;
	t_cube			*cube;
	t_raycasting	*ray;
}	t_key_event;

enum	e_key
{
	k_esc = 65307,
	k_w = 119,
	k_s = 115,
	k_a = 97,
	k_d = 100,
	k_q = 113,
	k_e = 101,
	k_up = 65362,
	k_do = 65364,
	k_ri = 65363,
	k_le = 65361,
};

enum	e_event
{
	KEY_DOWN = 2,
	KEY_UP = 3,
	BUTTON_PRESSED = 17
};

void	key_events(t_raycasting *ray, t_cube *cube);

int		loop(t_key_event *key);

#endif
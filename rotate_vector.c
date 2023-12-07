/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:03:52 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/07 16:06:28 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	rotate_vector(t_vector *vec, double deg)
{
	double	rad;
	double	swap;

	rad = deg * M_PI / 180;
	swap = vec->x;
	vec->x = cos(rad) * vec->x - sin(rad) * vec->y;
	vec->y = sin(rad) * swap + cos(rad) * vec->y;
}

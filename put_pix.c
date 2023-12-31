/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:00:27 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:50:07 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pix(t_image *im, int color, int x, int y)
{
	char	*new;

	new = im->img + (y * im->size + x * (im->bits / 8));
	*(unsigned int *) new = color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:00:27 by estelamb          #+#    #+#             */
/*   Updated: 2023/12/20 17:20:05 by estelamb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pix(t_image *im, int color, int x, int y)
{
	char	*new;

	new = im->img + (y * im->size + x * (im->bits / 8));
	*(unsigned int *) new = color;
}

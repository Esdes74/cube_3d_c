/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:35:29 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/13 14:05:54 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include "libft/libft.h"

typedef struct  s_color
{
    int first;
    int second;
    int third;
}   t_color;

typedef struct  s_cube 
{
    t_color f;
    t_color c;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    **map;
}   t_cube;

typedef enum e_error
{
    EXTENSION,
    OPEN,
}   t_error;

// Parsing
void    parsing(char *av, t_cube *cube);

// Error gestion
void    error(t_error err);

#endif
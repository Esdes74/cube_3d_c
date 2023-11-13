/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:35:29 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/13 14:05:54 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft/libft.h"

typedef struct s_cube 
{
    int     f[3];
    int     c[3];
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    **map;
}   t_cube;

typedef enum e_error
{
    EXTENSION,
}   t_error;

// Parsing
void    parsing(char *av, t_cube *cube);

// Error gestion
void    error(t_error err);

#endif
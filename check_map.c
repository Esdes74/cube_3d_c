/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:18:48 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 17:53:04 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_line(char *line);
static int	creat_map(t_list *lst, t_cube *cube);

void	check_map(int fd, t_cube *cube)
{
	t_list	*lst;
	char	*line;

	lst = (t_list *) malloc(sizeof(t_list));
	if (lst == NULL)
		return (close(fd), free_all(cube), error(MALLOC, END));
	lst = init_list(lst);
	line = get_next_line(fd);
	line = pass_newline(fd, line);
	if (!line)
		return (annihilation(lst, free, DEBUG), close(fd), free_all(cube), \
	error(EMPTY_MAP, END));
	while (line)
	{
		if (check_line(line))
			return (annihilation(lst, free, DEBUG), close(fd), free_all(cube), \
		exit(1));
		if (tailing_list(lst, line, STRING, DEBUG))
			return (annihilation(lst, free, DEBUG), close(fd), free_all(cube), \
		error(MALLOC, END));
		line = get_next_line(fd);
	}
	if (creat_map(lst, cube))
		return (annihilation(lst, free, DEBUG), close(fd), exit(1));
	annihilation(lst, none, DEBUG);
}

static int	check_line(char *line)
{
	static int	perso;
	int			i;

	i = -1;
	while (line[++i])
	{
		if (!ft_in(line[i], COMP))
		{
			if (ft_in(line[i], PERSO) && perso == 0)
				perso = 1;
			else if (ft_in(line[i], PERSO) && perso == 1)
				return (free(line), error(DOUBLE_PERSO, CONT), 1);
			else
				return (free(line), error(WRONG_COMPONENT, CONT), 1);
		}
	}
	return (0);
}

static int	creat_map(t_list *lst, t_cube *cube)
{
	int		i;
	t_cell	*tmp;

	cube->map = (char **) malloc(sizeof(char *) * (lst->len + 1));
	if (cube->map == NULL)
		return (free_all(cube), error(MALLOC, CONT), 1);
	cube->size_map = lst->len;
	tmp = lst->head;
	i = 0;
	while (tmp != NULL)
	{
		cube->map[i++] = tmp->data_cell->data;
		tmp = tmp->next;
	}
	cube->map[i] = NULL;
	return (0);
}

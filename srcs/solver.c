/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:19:52 by feedme            #+#    #+#             */
/*   Updated: 2018/10/26 03:50:41 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../grimly.h"

void	spreading(t_data data, t_path **head, char **cpy, t_path *last)
{
	pop_node(head);
	if ((last->coord.y > 0) &&
	cpy[last->coord.y - 1][last->coord.x] == data.empty.c)
		add_to_queue(head, last->coord.y - 1, last->coord.x, last);
	if ((last->coord.x > 0) &&
	cpy[last->coord.y][last->coord.x - 1] == data.empty.c)
		add_to_queue(head, last->coord.y, last->coord.x - 1, last);
	if ((last->coord.x < data.col_c) &&
	cpy[last->coord.y][last->coord.x + 1] == data.empty.c)
		add_to_queue(head, last->coord.y, last->coord.x + 1, last);
	if ((last->coord.y < data.line_c) &&
	cpy[last->coord.y + 1][last->coord.x] == data.empty.c)
		add_to_queue(head, last->coord.y + 1, last->coord.x, last);
	cpy[last->coord.y][last->coord.x] = data.wall.c;
	if (last->coord.y > 0)
		cpy[last->coord.y - 1][last->coord.x] = data.wall.c;
	if (last->coord.y < data.line_c)
		cpy[last->coord.y + 1][last->coord.x] = data.wall.c;
	if (last->coord.x > 0)
		cpy[last->coord.y][last->coord.x - 1] = data.wall.c;
	if (last->coord.x < data.col_c)
		cpy[last->coord.y][last->coord.x + 1] = data.wall.c;
}

void	draw_path(t_data data, t_path *path)
{
	int		steps;
	t_path	*tmp;

	steps = -1;
	while (path)
	{
		tmp = path->prev;
		steps++;
		data.map[path->coord.y][path->coord.x] = data.path.c;
		free(path);
		path = tmp;
	}
	data.map[data.entrance.coord.y][data.entrance.coord.x] = data.entrance.c;
	ft_printf("%dx%d%c%c", data.line_c, data.col_c, data.wall.c, data.empty.c);
	ft_printf("%c%c%c\n", data.path.c, data.entrance.c, data.exit_c);
	ft_putarray(data.map);
	ft_printf("RESULT IN %d STEPS!\n", steps);
}

int		find_solution(t_data data)
{
	t_path	*head;
	t_path	*last;
	char	**cpy;

	IF_RET(!(cpy = ft_mapdup(data.map)), 0);
	IF_X(!(head = (t_path*)malloc(sizeof(t_path))));
	head->coord.x = data.entrance.coord.x;
	head->coord.y = data.entrance.coord.y;
	head->next = NULL;
	head->prev = NULL;
	while (head)
	{
		last = next_in_queue(head);
		if (near_exit(last, data))
			break ;
		spreading(data, &head, cpy, last);
	}
	if (!head)
	{
		free_stuff(data, cpy, head);
		return (0);
	}
	draw_path(data, last);
	free_stuff(data, cpy, head);
	return (1);
}

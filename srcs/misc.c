/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:05:27 by feedme            #+#    #+#             */
/*   Updated: 2018/10/26 03:48:51 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../grimly.h"

t_exits	*add_exit(t_exits *xit, int x, int y)
{
	t_exits	*new;
	t_exits	*head;

	head = xit;
	IF_X(!(new = (t_exits*)malloc(sizeof(t_exits))));
	new->coord.x = x;
	new->coord.y = y;
	new->next = NULL;
	if (!xit)
		return (new);
	while (xit->next)
		xit = xit->next;
	xit->next = new;
	return (head);
}

void	init_data(t_data *data)
{
	data->line_c = 0;
	data->col_c = 0;
	data->wall.c = 0;
	data->wall.cnt = 0;
	data->empty.c = 0;
	data->empty.cnt = 0;
	data->path.c = 0;
	data->path.cnt = 0;
	data->entrance.c = 0;
	data->entrance.cnt = 0;
	data->exit_c = 0;
	data->exit = NULL;
}

int		near_exit(t_path *last, t_data data)
{
	while (data.exit)
	{
		if (last->coord.x == data.exit->coord.x &&
		last->coord.y == data.exit->coord.y)
			return (1);
		else if (last->coord.x == data.exit->coord.x &&
		last->coord.y - 1 == data.exit->coord.y)
			return (1);
		else if (last->coord.x - 1 == data.exit->coord.x &&
		last->coord.y == data.exit->coord.y)
			return (1);
		else if (last->coord.x + 1 == data.exit->coord.x &&
		last->coord.y == data.exit->coord.y)
			return (1);
		else if (last->coord.x == data.exit->coord.x &&
		last->coord.y + 1 == data.exit->coord.y)
			return (1);
		data.exit = data.exit->next;
	}
	return (0);
}

void	free_stuff(t_data data, char **cpy, t_path *head)
{
	int		i;
	t_exits	*tmp;
	t_path	*tmp2;

	i = -1;
	while (cpy[++i])
		free(cpy[i]);
	free(cpy);
	i = -1;
	while (data.map[++i])
		free(data.map[i]);
	free(data.map);
	while (data.exit)
	{
		tmp = data.exit->next;
		free(data.exit);
		data.exit = tmp;
	}
	while (head)
	{
		tmp2 = head->next;
		free(head);
		head = tmp2;
	}
}

void	space_saver(char *c, t_data *data, int i, int y)
{
	*c = data->entrance.c;
	data->entrance.cnt++;
	data->entrance.coord.x = i;
	data->entrance.coord.y = y;
}

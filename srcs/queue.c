/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:51:28 by feedme            #+#    #+#             */
/*   Updated: 2018/10/26 02:54:57 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../grimly.h"

t_path	*next_in_queue(t_path *head)
{
	t_path	*cpy;

	IF_X(!(cpy = (t_path*)malloc(sizeof(t_path))));
	while (head->next)
		head = head->next;
	cpy->coord.x = head->coord.x;
	cpy->coord.y = head->coord.y;
	cpy->prev = head->prev;
	return (cpy);
}

void	pop_node(t_path **head)
{
	t_path	*tmp;

	tmp = *head;
	if (!(*head)->next)
	{
		free(*head);
		*head = NULL;
	}
	else
	{
		while (tmp->next->next)
			tmp = tmp->next;
		free(tmp->next);
		tmp->next = NULL;
	}
}

void	add_to_queue(t_path **head, int y, int x, t_path *last)
{
	t_path	*new;

	IF_X(!(new = (t_path*)malloc(sizeof(t_path))));
	new->coord.y = y;
	new->coord.x = x;
	new->prev = last;
	new->next = *head;
	*head = new;
}

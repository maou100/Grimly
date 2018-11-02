/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 02:56:11 by feedme            #+#    #+#             */
/*   Updated: 2018/10/26 03:49:57 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H

# include "libft.h"

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_exits
{
	struct s_coord	coord;
	struct s_exits	*next;
}					t_exits;

typedef struct		s_chars
{
	char			c;
	int				cnt;
	struct s_coord	coord;
}					t_chars;

typedef struct		s_data
{
	int				line_c;
	int				col_c;
	struct s_chars	wall;
	struct s_chars	empty;
	struct s_chars	path;
	struct s_chars	entrance;
	char			exit_c;
	struct s_exits	*exit;
	char			**map;
}					t_data;

typedef struct		s_path
{
	struct s_coord	coord;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

int					get_first_line(int fd, char **line);
int					find_solution(t_data data);
char				**check_and_get_map(int fd, t_data *data);
int					get_data(t_data *data, int fd);
t_exits				*add_exit(t_exits *xit, int x, int y);
void				init_data(t_data *data);
void				free_stuff(t_data data, char **cpy, t_path *head);
t_path				*next_in_queue(t_path *head);
void				add_to_queue(t_path **head, int y, int x, t_path *last);
int					near_exit(t_path *last, t_data data);
void				pop_node(t_path **head);
void				space_saver(char *c, t_data *data, int i, int y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:04:11 by feedme            #+#    #+#             */
/*   Updated: 2018/10/28 21:57:48 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../grimly.h"

int		get_chars(char *line, t_data *data)
{
	int		len;

	len = ft_strlen(line);
	if (len > 17 || len < 8)
		return (0);
	data->exit_c = line[--len];
	data->entrance.c = line[--len];
	data->path.c = line[--len];
	data->empty.c = line[--len];
	data->wall.c = line[--len];
	return (len);
}

int		get_line_col(char *line, t_data *data, int wall_i)
{
	int		i;
	int		i0;

	i = 0;
	IF_RET(line[i] == '0', 0);
	while (line[i] && line[i] != 'x')
	{
		if (!(IS_DIGIT(line[i])))
			return (0);
		i++;
	}
	if (i > 9 || !(data->line_c = ft_atoi(ft_strsub(line, 0, i))) ||
	!(line[i0 = ++i] >= '1' && line[i] <= '9'))
		return (0);
	while (i < wall_i && IS_DIGIT(line[i]) &&
	(data->line_c * data->col_c <= 1000000000) && i - i0 + 1 < 10)
	{
		data->col_c = ft_atoi(ft_strsub(line, i0, i - i0 + 1));
		i++;
	}
	if (i != wall_i || data->line_c * data->col_c > 1000000000)
		return (0);
	return (1);
}

int		get_data(t_data *data, int fd)
{
	int		wall_i;
	char	*line;

	if (!get_first_line(fd, &line))
	{
		FREE(line);
		return (0);
	}
	init_data(data);
	if (!(wall_i = get_chars(line, data)) ||
	!(get_line_col(line, data, wall_i)))
	{
		FREE(line);
		return (0);
	}
	FREE(line);
	return (1);
}

int		fill_map(char *map, t_data *data, char *line, int y)
{
	int		i;

	i = -1;
	while (line[++i] != '\n')
	{
		if (((!i || !line[i + 1]) && line[i] == data->empty.c) ||
		((!y || y == (data->line_c) - 1) && line[i] == data->empty.c))
			return (0);
		if (line[i] == data->wall.c && (data->wall.cnt = 1))
			map[i] = data->wall.c;
		else if (line[i] == data->empty.c && (data->empty.cnt = 1))
			map[i] = data->empty.c;
		else if (line[i] == data->entrance.c)
			space_saver(map + i, data, i, y);
		else if (line[i] == data->exit_c && (map[i] = data->exit_c))
			data->exit = add_exit(data->exit, i, y);
		else
			return (0);
	}
	return (1);
}

char	**check_and_get_map(int fd, t_data *data)
{
	char	**map;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	IF_X(!(map = ft_create_map(data->line_c, data->col_c, data->empty.c)));
	IF_X(!(line = ft_strnew(data->col_c + 1)));
	while ((ret = read(fd, line, data->col_c + 1)) > 0)
	{
		IF_RET((ret != data->col_c + 1), NULL);
		IF_RET(!(fill_map(map[i], data, line, i)), NULL);
		i++;
		ft_bzero(line, data->col_c + 1);
	}
	FREE(line);
	IF_X((ret == -1));
	IF_RET((i != data->line_c || data->entrance.cnt != 1 || !data->exit ||
	!data->empty.cnt || !data->wall.cnt), NULL);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 21:08:01 by feedme            #+#    #+#             */
/*   Updated: 2018/10/29 01:31:17 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../grimly.h"

int		get_first_line(int fd, char **line)
{
	char	c;
	int		ret;
	int		i;

	i = -1;
	IF_X(!((*line) = ft_strnew(18)));
	while ((ret = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break ;
		if (i > 17)
			return (0);
		(*line)[++i] = c;
	}
	if (ret == -1)
	{
		free((*line));
		exit(0);
	}
	if (c != '\n')
	{
		free((*line));
		return (0);
	}
	return (1);
}

int		ft_grimly(int fd)
{
	t_data	data;

	if (!(get_data(&data, fd)))
		return (0);
	if (!(data.map = check_and_get_map(fd, &data)) ||
	!(find_solution(data)))
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	int		i;
	int		fd;

	i = 0;
	if (ac == 1)
	{
		if (!(ft_grimly(0)))
			ft_putstr_fd("MAP ERROR\n", 2);
	}
	else
	{
		while (i < ac)
		{
			fd = open(av[++i], O_RDONLY);
			if (!ft_grimly(fd))
				ft_putstr_fd("MAP ERROR\n", 2);
			close(fd);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:46:16 by aperrein          #+#    #+#             */
/*   Updated: 2023/09/28 18:28:06 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_init_pos(char c, t_data *data, int j, int i)
{
	if (c == ' ' || c == '1' || c == '0' || c == '\n')
		return ;
	data->x = i + 0.5;
	data->y = j + 0.5;
	data->start_player = c;
	data->map[j][i] = '0';
	data->nbr_player++;
}

void	check_player(t_data *data)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			c = data->map[j][i];
			if (c == '0' || c == '1' || c == ' ' || c == 'N'
				|| c == 'W' || c == 'S' || c == 'E' || c == '\n')
				check_init_pos(c, data, j, i);
			else
				data->map_error = 1;
			i++;
		}
		j++;
	}
	if (data->map_error)
		free_error(data, "Error\nUnauthorized character in the map\n");
}

void	recur_path(t_data *data, int y, int x)
{
	if (data->clone[y][x] == '1' || data->clone[y][x] == '2')
		return ;
	if (x == 0 || !data->clone[y][x + 1] || y == 0 || !data->clone[y + 1])
	{
		data->error_wall = 1;
		return ;
	}
	if (data->clone[y][x] == ' ')
		data->error_wall = 1;
	data->clone[y][x] = '2';
	recur_path(data, y, x - 1);
	recur_path(data, y, x + 1);
	recur_path(data, y - 1, x);
	recur_path(data, y + 1, x);
}

void	check_surrounded(t_data *data)
{
	data->error_wall = 0;
	data->clone = clone(data);
	recur_path(data, data->y, data->x);
	free_tab(data->clone);
	if (data->error_wall)
		free_error(data, "Error\nMap not surrounded by wall\n");
}

void	check_map(t_data *data)
{
	data->nbr_player = 0;
	data->map_error = 0;
	check_player(data);
	if (data->nbr_player != 1)
		free_error(data, "Error\nNumber of player not correct\n");
	if (data->file)
		check_surrounded(data);
}

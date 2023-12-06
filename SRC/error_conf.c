/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:46:21 by aperrein          #+#    #+#             */
/*   Updated: 2023/09/28 18:40:57 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *s)
{
	ft_printf("%s\n", s);
	return (0);
}

void	free_data(t_data *data)
{
	if (data->ceiling.name)
		free(data->ceiling.name);
	if (data->floor.name)
		free(data->floor.name);
	if (data->no_p)
		free(data->no_p);
	if (data->we_p)
		free(data->we_p);
	if (data->ea_p)
		free(data->ea_p);
	if (data->so_p)
		free(data->so_p);
	free_tab(data->file);
	data->file = 0;
	free_tab(data->map);
	data->map = 0;
}

void	free_error(t_data *data, char *s)
{
	free_data(data);
	data->no_p = 0;
	data->we_p = 0;
	data->ea_p = 0;
	data->so_p = 0;
	data->floor.name = 0;
	data->ceiling.name = 0;
	ft_printf("%s", s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:41:20 by aperrein          #+#    #+#             */
/*   Updated: 2023/10/02 18:05:19 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_identifier(t_data *data, char **line)
{
	if (!ft_strncmp(line[0], "NO", 2) && !data->no_p)
		data->no_p = ft_strtrim(line[1], "\n");
	else if (!ft_strncmp(line[0], "SO", 2) && !data->so_p)
		data->so_p = ft_strtrim(line[1], "\n");
	else if (!ft_strncmp(line[0], "WE", 2) && !data->we_p)
		data->we_p = ft_strtrim(line[1], "\n");
	else if (!ft_strncmp(line[0], "EA", 2) && !data->ea_p)
		data->ea_p = ft_strtrim(line[1], "\n");
	else if (!ft_strncmp(line[0], "F", 1) && !data->floor.name)
		data->floor.name = ft_strtrim(line[1], "\n");
	else if (!ft_strncmp(line[0], "C", 1) && !data->ceiling.name)
		data->ceiling.name = ft_strtrim(line[1], "\n");
	else
		data->conf_error = 1;
}

void	recup_element(t_data *data, char *s)
{
	char	**line;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(s, "\n");
	line = ft_split(tmp, ' ');
	free(tmp);
	while (line[i])
		i++;
	if (i != 2 && !data->configured)
	{
		data->conf_error = 1;
		free_tab(line);
		return ;
	}
	select_identifier(data, line);
	if (data->no_p && data->so_p && data->we_p && data->ea_p \
		&& data->floor.name && data->ceiling.name)
		data->configured = 1;
	free_tab(line);
}

int	element_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->file_lenght && !data->configured)
	{
		if (!empty_line(data->file[i]))
			recup_element(data, data->file[i]);
		i++;
	}
	while (i < data->file_lenght && empty_line(data->file[i]))
		i++;
	data->map = malloc(sizeof(char *) * (data->file_lenght - i + 1));
	while (i < data->file_lenght)
		data->map[j++] = ft_strdup(data->file[i++]);
	data->map[j] = 0;
	if (data->conf_error)
		free_error(data, "Error\nConfiguration issues\n");
	return (0);
}

int	text_check(t_data *data)
{
	if (access(data->we_p, R_OK))
		return (error("Error\nWrong west texture"));
	if (access(data->so_p, R_OK))
		return (error("Error\nWrong south texture"));
	if (access(data->no_p, R_OK))
		return (error("Error\nWrong north texture"));
	if (access(data->ea_p, R_OK))
		return (error("Error\nWrong east texture"));
	if (check_color(&data->floor))
		return (error("Error\nWrong floor informations"));
	if (check_color(&data->ceiling))
		return (error("Error\nWrong ceiling informations"));
	return (1);
}

void	conf_check(t_data *data)
{
	data->ceiling.name = 0;
	data->floor.name = 0;
	data->no_p = 0;
	data->so_p = 0;
	data->we_p = 0;
	data->ea_p = 0;
	data->x = 0;
	data->y = 0;
	element_check(data);
	if (data->conf_error)
		return ;
	if (!text_check(data))
		free_error(data, "");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:51:28 by aperrein          #+#    #+#             */
/*   Updated: 2023/09/28 18:23:49 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	number_rgb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

int	three_color(char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(s, ',');
	while (tab[i])
		i++;
	free_tab(tab);
	if (i != 3)
		return (0);
	return (1);
}

int	in_color_range(int a)
{
	if (a <= 255 && a >= 0)
		return (1);
	return (0);
}

int	fill_color(t_color *color)
{
	char	**tab;

	tab = ft_split(color->name, ',');
	color->r = ft_atoi(tab[0]);
	color->g = ft_atoi(tab[1]);
	color->b = ft_atoi(tab[2]);
	free_tab(tab);
	if (in_color_range(color->r) && in_color_range(color->g)
		&& in_color_range(color->b))
		return (0);
	return (1);
}

int	check_color(t_color *color)
{
	if (!number_rgb(color->name))
		return (1);
	if (!three_color(color->name))
		return (1);
	if (fill_color(color))
		return (1);
	return (0);
}

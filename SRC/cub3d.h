/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:43:15 by aperrein          #+#    #+#             */
/*   Updated: 2023/10/04 18:03:52 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define WIDTH 1920
# define HEIGHT 1080
# define TEXTURE 50

typedef struct s_color
{
	char	*name;
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_img
{
	int		height;
	int		width;
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_moves
{
	int		move_forward;
	int		move_back;
	int		step_to_left;
	int		step_to_right;
	int		rotate_left;
	int		rotate_right;
	double	move_speed;
	double	rotate_speed;
}	t_moves;

typedef struct s_text
{
	int		n_text;
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		color;
	double	wall_x;
}				t_text;

typedef struct s_ray
{
	double	camerax;
	double	ray_dirx;
	double	ray_diry;
	double	ray_dirx0;
	double	ray_diry0;
	double	ray_dirx1;
	double	ray_diry1;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	perp_wall_dist;
	int		mapx;
	int		mapy;
	double	step;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		var_x;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	void		*actual_text;
	int			file_lenght;
	int			configured;
	int			conf_error;
	int			map_error;
	int			nbr_player;
	int			error_wall;
	int			count;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			fl;
	int			ce;
	int			rx;
	int			ry;
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		p_angle;
	char		**file;
	char		**map;
	char		**clone;
	char		*no_p;
	char		*so_p;
	char		*we_p;
	char		*ea_p;
	char		start_player;
	t_color		floor;
	t_color		ceiling;
	t_img		img;
	t_img		img_n;
	t_img		img_so;
	t_img		img_ea;
	t_img		img_we;
	t_moves		moves;
	t_ray		ray;
	t_text		texture;
}				t_data;

char	**clone(t_data *data);

int		number_rgb(char *s);
int		three_color(char *s);
int		in_color_range(int a);
int		fill_color(t_color *color);
int		check_color(t_color *color);
int		element_check(t_data *data);
int		text_check(t_data *data);
int		file_check(int argc, char *file);
int		line_nb(char *s, t_data *data);
int		conf_init(int argc, char *argv[], t_data *data);
int		error(char *s);
int		ft_finish(t_data *data);
int		handle_input(int keysym, t_data *data);
int		handle_input_release(int keysym, t_data *data);
int		view(t_data *data);
int		cub_check(char *s);
int		empty_line(char *s);

void	check_init_pos(char c, t_data *data, int j, int i);
void	check_player(t_data *data);
void	recur_path(t_data *data, int y, int x);
void	check_surrounded(t_data *data);
void	check_map(t_data *data);
void	select_identifier(t_data *data, char **line);
void	recup_element(t_data *data, char *s);
void	conf_check(t_data *data);
void	conf_fill(char *file, t_data *data);
void	conf_read(char *s, t_data *data);
void	free_data(t_data *data);
void	free_error(t_data *data, char *s);
void	ft_free_map(t_data *data);
void	ft_moves_ws(t_data *data);
void	ft_moves_ad(t_data *data);
void	ft_rotate1(t_data *data);
void	ft_rotate2(t_data *data);
void	init_dir(t_data *data);
void	init_ray(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	background(t_data *data);
void	raycasting(t_data *data);
void	game_init(t_data *data);
void	img_init(t_data *data);
void	texture_choice(t_data *data);
void	texture_choice2(t_data *data);
void	raycasting1(t_data *data);
void	raycasting2(t_data *data);
void	raycasting_hit(t_data *data);
void	raycasting3(t_data *data);
void	raycasting4(t_data *data);
void	raycasting5(t_data *data);
void	free_tab(char **tab);

#endif
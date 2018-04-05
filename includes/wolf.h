/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:23:52 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 21:35:52 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include "libft.h"
# include "get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_X 1000
# define WIN_Y 700
# define TXTR_X 64
# define TXTR_Y 64
# define EXIT 53
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define TURN_R 124
# define TURN_L 123
# define RUN 257
# define SPACE 49
# define RETURN 36
# define MV_SPD 0.07
# define MV_RUN 0.50
# define RT_SPD 0.08
# define BLACK 0x000000
# define RED 0xFF0000

typedef struct		s_texture
{
	int				width;
	int				height;
	char			*data;
}					t_texture;

typedef struct		s_env
{
	int				fd;
	int				nb_columns;
	int				nb_points;
	int				nb_lines;
	int				player_x;
	int				player_y;
	int				**map;
	unsigned long	color;
	int				dec;
	int				last_x;
	t_texture		*img;
	char			*line;
	char			**tab;
	int				bx0;
	int				by0;
	int				bx1;
	int				by1;
	void			*mlx;
	void			*win;
	int				bpp;
	int				sizeline;
	int				endian;
	char			*data;
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			old_plane_x;
	float			old_plane_y;
	float			camera_x;
	float			ray_pos_x;
	float			ray_pos_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			old_dir_x;
	float			old_dir_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				step_x;
	int				step_y;
	float			wall_dist;
	float			wall_x;
	int				map_x;
	int				map_y;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
	int				line_height;
	int				up;
	int				down;
	int				left;
	int				right;
	int				rt_right;
	int				rt_left;
	float			mv_spd;
	int				intro;
	int				scroll;
	int				game;
	int				shot;
	int				shot_cpt;
	int				floor_flag;
	double			floor_dist;
	char			**text;
	int				text_nb_lines;
	double			floor_dist_x;
	double			floor_dist_y;
	int				floor_txtr_x;
	int				floor_txtr_y;
	clock_t			cpt;
	clock_t			cpt_scroll;
	clock_t			start_clock;
	clock_t			current_clock;
	clock_t			end_music;
	clock_t			last_frame;
	clock_t			next_frame;

	t_texture		*sky;
	t_texture		*wall;
	t_texture		*wolf;
	t_texture		*logo;
	t_texture		*w1;
	t_texture		*w2;
	t_texture		*w3;
	t_texture		*w4;
	t_texture		*floor;
}					t_env;

void				ft_pre_load_map(char *argv, t_env *e);
void				ft_load_map(char *argv, t_env *e);
void				ft_load_map_2(t_env *e, int i, int j);
void				ft_load_xpm(t_env *e);
void				ft_load_text_file(t_env *e);
void				ft_fill_pixel(t_env *e, int x, int y, unsigned long color);
void				ft_copy_sky(t_env *e);
void				ft_box(t_env *e, unsigned long color);
void				ft_show_mini_map(t_env *e);
int					ft_show_weapon(t_env *e);
void				ft_init_e(t_env *e);
void				ft_init_raycasting(t_env *e, int x);
void				ft_init_map(t_env *e);
void				ft_init_box(t_env *e, int i, int j);
void				ft_init_red_point(t_env *e, int i, int j);
void				ft_step(t_env *e);
void				ft_wall_hit(t_env *e);
void				ft_draw_this(t_env *e);
void				ft_wall_txtr(t_env *e, int x);
int					ft_raycast(t_env *e);
void				ft_floor(t_env *e, int x, int draw_end);
void				ft_floor_2(t_env *e, int x);
static void			ft_move_up(t_env *e);
static void			ft_move_down(t_env *e);
static void			ft_move_left(t_env *e);
static void			ft_move_right(t_env *e);
int					ft_set_move(t_env *e, int keycode);
int					ft_key_press(int keycode, t_env *e);
int					ft_key_release(int keycode, t_env *e);
void				ft_key_space(int keycode, t_env *e);
void				ft_manipulate_2(int x, int y, t_env *e);
int					ft_manipulate(int x, int y, t_env *e);
void				ft_scroll_text(t_env *e, int condition);
int					ft_intro(t_env *e);
void				ft_intro_2(t_env *e);
int					ft_show_image(t_env *e);
void				ft_exit(t_env *e, int error, char *text);
static void			ft_free_tab(char **tab);
void				ft_mlx_hook(t_env *e);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 03:28:59 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:19:53 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_init_e(t_env *e)
{
	e->dir_x = -1;
	e->dir_y = 0;
	e->plane_x = 0;
	e->plane_y = 1;
	e->mv_spd = 0.08;
	e->dec = 100;
	e->scroll = 0;
	e->shot = 0;
	e->game = 0;
	e->next_frame = 0;
	e->last_frame = 0;
	e->floor_flag = 1;
	e->intro = 0;
}

/*
** Start point and ray direction x, y
*/

void		ft_init_raycasting(t_env *e, int x)
{
	e->camera_x = (2 * x / (double)WIN_X) - 1;
	e->ray_pos_x = e->pos_x;
	e->ray_pos_y = e->pos_y;
	e->ray_dir_x = e->dir_x + e->plane_x * e->camera_x;
	e->ray_dir_y = e->dir_y + e->plane_y * e->camera_x;
}

/*
** In what case is the cam
** Length of the ray between each intersection
*/

void		ft_init_map(t_env *e)
{
	e->map_x = (int)e->ray_pos_x;
	e->map_y = (int)e->ray_pos_y;
	e->delta_dist_x = sqrt(1 + (e->ray_dir_y * e->ray_dir_y)
		/ (e->ray_dir_x * e->ray_dir_x));
	e->delta_dist_y = sqrt(1 + (e->ray_dir_x * e->ray_dir_x)
		/ (e->ray_dir_y * e->ray_dir_y));
	e->hit = 0;
}

void		ft_init_box(t_env *e, int i, int j)
{
	e->bx0 = 9 + i * 4;
	e->by0 = 19 + j * 4;
	e->bx1 = i * 4 + 14;
	e->by1 = 24 + j * 4;
}

void		ft_init_red_point(t_env *e, int i, int j)
{
	e->bx0 = 10 + i * 4;
	e->by0 = 20 + j * 4;
	e->bx1 = i * 4 + 14;
	e->by1 = 24 + j * 4;
}

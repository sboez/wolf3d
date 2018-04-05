/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 03:28:07 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:28:35 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

/*
** Direction vector calcul and length between two segments
*/

void		ft_step(t_env *e)
{
	if (e->ray_dir_x < 0)
	{
		e->step_x = -1;
		e->side_dist_x = (e->ray_pos_x - e->map_x) * e->delta_dist_x;
	}
	else
	{
		e->step_x = 1;
		e->side_dist_x = (e->map_x + 1.0 - e->ray_pos_x) * e->delta_dist_x;
	}
	if (e->ray_dir_y < 0)
	{
		e->step_y = -1;
		e->side_dist_y = (e->ray_pos_y - e->map_y) * e->delta_dist_y;
	}
	else
	{
		e->step_y = 1;
		e->side_dist_y = (e->map_y + 1.0 - e->ray_pos_y) * e->delta_dist_y;
	}
}

/*
** Check if there is a wall
** No wall ? So, move to the next case on x or y
*/

void		ft_wall_hit(t_env *e)
{
	while (e->hit == 0)
	{
		if (e->side_dist_x < e->side_dist_y)
		{
			e->side_dist_x += e->delta_dist_x;
			e->map_x += e->step_x;
			e->side = 0;
		}
		else
		{
			e->side_dist_y += e->delta_dist_y;
			e->map_y += e->step_y;
			e->side = 1;
		}
		if (e->map[e->map_x][e->map_y] > 0)
			e->hit = 1;
	}
}

/*
** Correction distance calcul for the projection
** Calcul the height of the line to draw
** Calcul max top and max low's pixels to draw
** Limit areas draws to screen only
*/

void		ft_draw_this(t_env *e)
{
	if (e->side == 0)
		e->wall_dist = ((e->map_x - e->ray_pos_x +
			(1 - e->step_x) / 2) / e->ray_dir_x);
	else
		e->wall_dist = ((e->map_y - e->ray_pos_y +
			(1 - e->step_y) / 2) / e->ray_dir_y);
	e->line_height = (int)(WIN_Y / e->wall_dist);
	e->draw_start = (-e->line_height / 2 + WIN_Y / 2);
	e->draw_end = (e->line_height / 2 + WIN_Y / 2);
	if (e->draw_start < 0)
		e->draw_start = 0;
	if (e->draw_end >= WIN_Y)
		e->draw_end = WIN_Y - 1;
}

void		ft_wall_txtr(t_env *e, int x)
{
	int txtr_x;
	int txtr_y;
	int y;
	int d;

	txtr_x = e->wall_x * (float)TXTR_X;
	y = e->draw_start;
	if (e->side == 0 && e->ray_dir_x > 0)
		txtr_x = TXTR_X - txtr_x - 1;
	if (e->side == 1 && e->ray_dir_y < 0)
		txtr_x = TXTR_X - txtr_x - 1;
	while (y < e->draw_end)
	{
		d = y * 256 - WIN_Y * 128 + e->line_height * 128;
		txtr_y = ((d * TXTR_Y) / e->line_height) / 256;
		e->color = ((unsigned int *)(e->wall->data))[TXTR_Y * txtr_y + txtr_x];
		if (e->side == 1)
			e->color = (e->color >> 1) & 0x7F7F7F;
		ft_fill_pixel(e, x, y, e->color);
		y++;
	}
}

int			ft_raycast(t_env *e)
{
	int x;

	x = 0;
	while (x < WIN_X)
	{
		ft_init_raycasting(e, x);
		ft_init_map(e);
		ft_step(e);
		ft_wall_hit(e);
		ft_draw_this(e);
		if (e->side == 0)
			e->wall_x = e->ray_pos_y + e->wall_dist * e->ray_dir_y;
		else
			e->wall_x = e->ray_pos_x + e->wall_dist * e->ray_dir_x;
		e->wall_x -= floor((e->wall_x));
		ft_wall_txtr(e, x);
		if (e->floor_flag > 0)
			ft_floor(e, x, e->draw_end);
		x++;
	}
	return (0);
}

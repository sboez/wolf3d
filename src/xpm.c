/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:29:19 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:30:08 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_load_xpm(t_env *e)
{
	int		x;
	int		y;

	if (!((e->sky = mlx_xpm_file_to_image(e->mlx, "xpm/sky.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : sky");
	if (!((e->wall = mlx_xpm_file_to_image(e->mlx, "xpm/brick.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : wall");
	if (!((e->w1 = mlx_xpm_file_to_image(e->mlx, "xpm/w1.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : weapon1");
	if (!((e->w2 = mlx_xpm_file_to_image(e->mlx, "xpm/w2.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : weapon2");
	if (!((e->w3 = mlx_xpm_file_to_image(e->mlx, "xpm/w4.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : weapon3");
	if (!((e->w4 = mlx_xpm_file_to_image(e->mlx, "xpm/w7.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : weapon4");
	if (!((e->wolf = mlx_xpm_file_to_image(e->mlx, "xpm/wolf.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : wolf");
	if (!((e->floor = mlx_xpm_file_to_image(e->mlx, "xpm/floor.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : floor");
	if (!((e->logo = mlx_xpm_file_to_image(e->mlx, "xpm/logo.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : logo");
	if (!((e->wolf = mlx_xpm_file_to_image(e->mlx, "xpm/wolf.xpm", &x, &y))))
		ft_exit(e, 2, "Error texture : wolf");
}

void		ft_floor_2(t_env *e, int x)
{
	int		y;

	y = e->draw_end;
	while (y < WIN_Y)
	{
		e->floor_dist = ((WIN_Y / (2.0 * y - WIN_Y)) / e->wall_dist);
		e->floor_txtr_x = (int)((e->floor_dist * e->floor_dist_x +
					(1.0 - e->floor_dist) * e->pos_x) * TXTR_X) % TXTR_X;
		e->floor_txtr_y = (int)((e->floor_dist * e->floor_dist_y +
					(1.0 - e->floor_dist) * e->pos_y) * TXTR_Y) % TXTR_Y;
		ft_fill_pixel(e, x, y, ((unsigned int *)(e->floor->data))
				[TXTR_X * e->floor_txtr_y + e->floor_txtr_x]);
		y++;
	}
}

void		ft_floor(t_env *e, int x, int draw_end)
{
	if (e->side == 0 && e->ray_dir_x > 0)
	{
		e->floor_dist_x = e->map_x;
		e->floor_dist_y = e->map_y + e->wall_x;
	}
	else if (e->side == 0 && e->ray_dir_x < 0)
	{
		e->floor_dist_x = e->map_x + 1.0;
		e->floor_dist_y = e->map_y + e->wall_x;
	}
	else if (e->side == 1 && e->ray_dir_y > 0)
	{
		e->floor_dist_x = e->map_x + e->wall_x;
		e->floor_dist_y = e->map_y;
	}
	else
	{
		e->floor_dist_x = e->map_x + e->wall_x;
		e->floor_dist_y = e->map_y + 1.0;
	}
	ft_floor_2(e, x);
}

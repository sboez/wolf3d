/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 03:50:30 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:44:13 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_fill_pixel(t_env *e, int x, int y, unsigned long color)
{
	if (x < WIN_X && y < WIN_Y && x >= 0 && y >= 0)
		((unsigned int *)(e->img->data))[x + y * WIN_X] = color;
}

void		ft_copy_sky(t_env *e)
{
	int i;
	int ip;
	int end;
	int y;

	i = 0;
	ip = 0;
	end = 0;
	y = 0;
	if (e->dec <= 1)
		e->dec = 1920;
	while (y < 400)
	{
		ip = e->dec + y * 1920;
		i = y * WIN_X;
		end = i + WIN_X;
		while (i < end)
		{
			((unsigned int *)(e->img->data))[i] = ((unsigned int *)
			(e->sky->data))[ip];
			i++;
			ip++;
		}
		y++;
	}
}

void		ft_box(t_env *e, unsigned long color)
{
	int x;
	int y;

	y = e->by0;
	while (y < e->by1)
	{
		x = e->bx0;
		while (x < e->bx1)
		{
			ft_fill_pixel(e, x, y, color);
			x++;
		}
		y++;
	}
}

void		ft_show_mini_map(t_env *e)
{
	int i;
	int j;

	j = 0;
	while (j < e->nb_lines)
	{
		i = 0;
		while (i < e->nb_columns)
		{
			if (j == (int)e->pos_x && i == (int)e->pos_y)
			{
				ft_init_red_point(e, i, j);
				ft_box(e, RED);
			}
			if (e->map[j][i] != 0)
			{
				ft_init_box(e, i, j);
				ft_box(e, BLACK);
			}
			i++;
		}
		j++;
	}
}

int			ft_show_weapon(t_env *e)
{
	if (e->shot == 0)
		mlx_put_image_to_window(e->mlx, e->win, e->w1, (WIN_X - 600)
				/ 2, (WIN_Y - 600));
	else
	{
		e->shot_cpt++;
		if (e->shot_cpt >= 2 && e->shot_cpt < 4)
			mlx_put_image_to_window(e->mlx, e->win, e->w2, (WIN_X - 600) / 2,
					(WIN_Y - 600));
		if (e->shot_cpt >= 4 && e->shot_cpt < 6)
			mlx_put_image_to_window(e->mlx, e->win, e->w3, (WIN_X - 600) / 2,
					(WIN_Y - 600));
		if (e->shot_cpt >= 6 && e->shot_cpt < 8)
			mlx_put_image_to_window(e->mlx, e->win, e->w4, (WIN_X - 600) / 2,
					(WIN_Y - 600));
		if (e->shot_cpt >= 8)
		{
			mlx_put_image_to_window(e->mlx, e->win, e->w1, (WIN_X - 600) / 2,
					(WIN_Y - 600));
			e->shot_cpt = 0;
			e->shot = 0;
		}
	}
	return (0);
}

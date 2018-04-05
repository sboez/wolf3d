/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 03:45:09 by sboez             #+#    #+#             */
/*   Updated: 2017/09/27 03:46:07 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_manipulate_2(int x, int y, t_env *e)
{
	if (x > e->last_x)
	{
		e->old_dir_x = e->dir_x;
		e->dir_x = e->dir_x * cos(-RT_SPD) - e->dir_y * sin(-RT_SPD);
		e->dir_y = e->old_dir_x * sin(-RT_SPD) + e->dir_y * cos(-RT_SPD);
		e->old_plane_x = e->plane_x;
		e->plane_x = e->plane_x * cos(-RT_SPD) - e->plane_y * sin(-RT_SPD);
		e->plane_y = e->old_plane_x * sin(-RT_SPD) + e->plane_y * cos(-RT_SPD);
		e->dec -= 1;
	}
}

int			ft_manipulate(int x, int y, t_env *e)
{
	if (x > 0 && y > 0 && x < WIN_X && y < WIN_Y)
	{
		if (x < e->last_x)
		{
			e->old_dir_x = e->dir_x;
			e->dir_x = e->dir_x * cos(RT_SPD) - e->dir_y * sin(RT_SPD);
			e->dir_y = e->old_dir_x * sin(RT_SPD) + e->dir_y * cos(RT_SPD);
			e->old_plane_x = e->plane_x;
			e->plane_x = e->plane_x * cos(RT_SPD) - e->plane_y * sin(RT_SPD);
			e->plane_y = e->old_plane_x * sin(RT_SPD) + e->plane_y
			* cos(RT_SPD);
			e->dec += 1;
		}
		ft_manipulate_2(x, y, e);
		e->last_x = x;
	}
	return (0);
}

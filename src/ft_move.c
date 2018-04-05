/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:20:26 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:38:29 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void		ft_move_up(t_env *e)
{
	if (!(e->map[(int)(e->pos_x + e->dir_x * e->mv_spd)][(int)e->pos_y]))
		e->pos_x += e->dir_x * e->mv_spd;
	if (!(e->map[(int)e->pos_x][(int)(e->pos_y + e->dir_y * e->mv_spd)]))
		e->pos_y += e->dir_y * e->mv_spd;
}

static void		ft_move_down(t_env *e)
{
	if (!(e->map[(int)(e->pos_x - e->dir_x * e->mv_spd)][(int)e->pos_y]))
		e->pos_x -= e->dir_x * e->mv_spd;
	if (!(e->map[(int)e->pos_x][(int)(e->pos_y - e->dir_y * e->mv_spd)]))
		e->pos_y -= e->dir_y * e->mv_spd;
}

static void		ft_move_left(t_env *e)
{
	if (!(e->map[(int)(e->pos_x - e->plane_x * e->mv_spd)][(int)e->pos_y]))
		e->pos_x -= e->plane_x * e->mv_spd;
	if (!(e->map[(int)e->pos_x][(int)(e->pos_y - e->plane_y * e->mv_spd)]))
		e->pos_y -= e->plane_y * e->mv_spd;
}

static void		ft_move_right(t_env *e)
{
	if (!(e->map[(int)(e->pos_x + e->plane_x * e->mv_spd)][(int)e->pos_y]))
		e->pos_x += e->plane_x * e->mv_spd;
	if (!(e->map[(int)e->pos_x][(int)(e->pos_y + e->plane_y * e->mv_spd)]))
		e->pos_y += e->plane_y * e->mv_spd;
}

int				ft_set_move(t_env *e, int keycode)
{
	if (e->up == 1)
		ft_move_up(e);
	if (e->down == 1)
		ft_move_down(e);
	if (e->left == 1)
		ft_move_left(e);
	if (e->right == 1)
		ft_move_right(e);
	return (0);
}

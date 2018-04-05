/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:59:04 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 21:03:00 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_key_space(int keycode, t_env *e)
{
	if (keycode == SPACE && e->intro < 0 && e->shot == 0)
	{
		system("afplay  ./sound/shot.wav&");
		e->shot = 1;
	}
	if (keycode == SPACE && e->intro > 0)
	{
		e->intro = -1;
		e->cpt = 0;
		system("killall afplay 2&>/dev/null >/dev/null\n afplay \
				./song/lastv8.mp3&");
		e->start_clock = clock();
		e->end_music = e->start_clock + (1000000 * 157);
		e->game = 1;
	}
}

int			ft_key_press(int keycode, t_env *e)
{
	if (keycode == EXIT)
		ft_exit(e, 0, " ");
	ft_key_space(keycode, e);
	if (keycode == RETURN)
		ft_init_e(e);
	if (e->intro < 0)
	{
		(keycode == UP) ? e->up = 1 : e->up;
		(keycode == DOWN) ? e->down = 1 : e->down;
		(keycode == RIGHT) ? e->right = 1 : e->right;
		(keycode == RUN) ? e->mv_spd = 0.20 : e->mv_spd;
		(keycode == LEFT) ? e->left = 1 : e->left;
	}
	ft_set_move(e, keycode);
	return (0);
}

int			ft_key_release(int keycode, t_env *e)
{
	if (keycode == EXIT)
		exit(0);
	if (keycode == UP)
		e->up = 0;
	if (keycode == DOWN)
		e->down = 0;
	if (keycode == RIGHT)
		e->right = 0;
	if (keycode == LEFT)
		e->left = 0;
	if (keycode == RUN)
		e->mv_spd = 0.08;
	return (0);
}

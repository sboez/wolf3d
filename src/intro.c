/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:34:25 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:37:45 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_scroll_text(t_env *e, int condition)
{
	int l;
	int max;
	int i;

	max = ((WIN_Y - 231) / 2) + 265;
	i = 0;
	while (i < e->text_nb_lines)
	{
		if (WIN_Y - e->scroll + i * 25 > max)
		{
			mlx_string_put(e->mlx, e->win, ((WIN_X - ft_strlen(e->text[i]) *
					10) / 2) - 24, (i * 25 + WIN_Y - e->scroll) - 2,
					0x000000, e->text[i]);
			mlx_string_put(e->mlx, e->win, ((WIN_X - ft_strlen(e->text[i]) * 10)
				/ 2) - 22, i * 25 + WIN_Y - e->scroll, 0xFFFFFF, e->text[i]);
		}
		if (WIN_Y - e->scroll + e->text_nb_lines * 25 > max)
			mlx_put_image_to_window(e->mlx, e->win, e->wolf, (WIN_X - 145) / 2,
				e->text_nb_lines * 25 + WIN_Y - e->scroll);
		i++;
	}
	if (condition == 1)
		e->scroll++;
	if (e->scroll > 500)
		e->scroll = 0;
}

void		ft_intro_2(t_env *e)
{
	if (e->current_clock < e->cpt)
	{
		mlx_string_put(e->mlx, e->win, ((WIN_X - 200) / 2) - 22, ((WIN_Y - 231)
			/ 2) + 248, 0X000000, "PRESS SPACE TO START");
		mlx_string_put(e->mlx, e->win, ((WIN_X - 200) / 2) - 19, ((WIN_Y - 231)
			/ 2) + 250, 0x0FFFFFF, "PRESS SPACE TO START");
	}
	if (e->current_clock < e->cpt + CLOCKS_PER_SEC / 2)
		;
	else
		e->cpt = clock() + CLOCKS_PER_SEC / 2;
}

int			ft_intro(t_env *e)
{
	e->current_clock = clock();
	if (e->intro == 0)
	{
		system("killall afplay 2&>/dev/null >/dev/null\n afplay ./song/g.mp3&");
		e->start_clock = clock();
		e->end_music = e->start_clock + (1000000 * 255);
		e->intro = 1;
	}
	if (e->current_clock > e->end_music)
		e->intro = 0;
	if (e->current_clock >= e->cpt_scroll)
	{
		ft_scroll_text(e, 1);
		e->cpt_scroll = clock() + CLOCKS_PER_SEC / 25;
	}
	else
		ft_scroll_text(e, 0);
	ft_intro_2(e);
	mlx_put_image_to_window(e->mlx, e->win, e->logo, (WIN_X - 755) / 2,
			(WIN_Y - 231) / 2);
	return (e->intro);
}

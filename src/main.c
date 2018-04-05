/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:53:34 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 21:06:48 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_exit(t_env *e, int error, char *text)
{
	if (error == 0)
		ft_putstr("Wolf3d was closed successfully.\n");
	if (error == 2)
	{
		ft_putstr("Error n°2 Loading error.\n");
		ft_putendl(text);
	}
	if (error == 3)
	{
		ft_putstr("Error n°3 Ouch ! Player position is out of the map.\n");
		ft_putendl(text);
	}
	if (error == 4)
	{
		ft_putstr("Error Malloc or MLX error");
		ft_putendl(text);
	}
	system("killall afplay");
	exit(EXIT_FAILURE);
}

int			ft_show_image(t_env *e)
{
	clock_t end_t;

	end_t = clock();
	ft_copy_sky(e);
	ft_raycast(e);
	ft_show_mini_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	(e->intro == 0 || e->intro == 1) ? e->intro = ft_intro(e) : e->intro;
	if (e->game == 1)
	{
		ft_show_weapon(e);
		if (e->last_frame > e->end_music)
		{
			system("killall afplay 2&>/dev/null >/dev/null\n afplay \
					./song/lastv8.mp3&");
			e->start_clock = clock();
			e->end_music = e->start_clock + (1000000 * 157);
		}
	}
	return (0);
}

int			ft_red_cross(t_env *e)
{
	ft_exit(e, 0, " ");
	return (0);
}

void		ft_mlx_hook(t_env *e)
{
	mlx_hook(e->win, 2, 3, ft_key_press, e);
	mlx_hook(e->win, 3, 3, ft_key_release, e);
	mlx_hook(e->win, 6, 3, ft_manipulate, e);
	mlx_hook(e->win, 17, 0, ft_red_cross, 0);
	mlx_loop_hook(e->mlx, ft_show_image, e);
}

int			main(int argc, char **argv)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		ft_exit(e, 4, "Error Malloc -> e");
	ft_pre_load_map(argv[1], e);
	ft_load_map(argv[1], e);
	ft_load_text_file(e);
	ft_init_e(e);
	if ((e->mlx = mlx_init()) == NULL)
		ft_puterror("Error mlx init", 1);
	if ((e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "WOLF 3D")) == NULL)
		ft_puterror("Error mlx window", 1);
	e->img = mlx_new_image(e->mlx, WIN_X, WIN_Y);
	ft_load_xpm(e);
	ft_mlx_hook(e);
	mlx_loop(e->mlx);
	return (0);
}

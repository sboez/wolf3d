/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 03:37:07 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 20:31:00 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	ft_free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
}

void		ft_pre_load_map(char *argv, t_env *e)
{
	e->nb_lines = 0;
	e->fd = open(argv, O_RDONLY);
	if (e->fd)
		while (get_next_line(e->fd, &e->line) == 1)
		{
			e->nb_columns = 0;
			e->tab = ft_strsplit(e->line, ' ');
			while (e->tab[e->nb_columns])
			{
				e->nb_columns++;
				e->nb_points++;
			}
			ft_free_tab(e->tab);
			free(e->line);
			e->nb_lines++;
		}
	close(e->fd);
}

void		ft_load_map_2(t_env *e, int i, int j)
{
	while (e->tab[j])
	{
		e->map[i][j] = atoi(e->tab[j]);
		if (atoi(e->tab[j]) == 9)
		{
			e->pos_x = (double)i;
			e->pos_y = (double)j;
			e->map[i][j] = 0;
		}
		j++;
	}
}

void		ft_load_map(char *argv, t_env *e)
{
	int		i;
	int		j;

	i = 0;
	if (!(e->map = malloc(e->nb_lines * sizeof(unsigned int*))))
		ft_exit(e, 4, "Error malloc : e->map");
	e->fd = open(argv, O_RDONLY);
	if (e->fd < 3)
		ft_exit(e, 2, "Map file (in load)");
	while (get_next_line(e->fd, &e->line) == 1)
	{
		j = 0;
		if (!(e->map[i] = malloc(e->nb_columns * sizeof(unsigned int))))
			ft_exit(e, 4, "Error malloc : e->map[i]");
		e->tab = ft_strsplit(e->line, ' ');
		ft_load_map_2(e, i, j);
		ft_free_tab(e->tab);
		free(e->line);
		i++;
	}
	close(e->fd);
}

void		ft_load_text_file(t_env *e)
{
	int		i;
	int		j;

	if (!(e->text = malloc(e->nb_lines * sizeof(char*))))
		ft_exit(e, 4, "Error malloc : e->text");
	i = 0;
	e->fd = open("scroll_text.txt", O_RDONLY);
	if (e->fd < 3)
		ft_exit(e, 2, "Scroll text");
	while (get_next_line(e->fd, &e->line) == 1)
	{
		e->tab = ft_strsplit(e->line, '@');
		e->text[i] = ft_strdup(e->tab[0]);
		ft_free_tab(e->tab);
		free(e->line);
		i++;
	}
	close(e->fd);
	e->text_nb_lines = i;
}

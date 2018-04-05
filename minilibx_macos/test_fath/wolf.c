#include "libft/includes/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
# include "minilibx_macos/mlx.h"
#include <math.h>

# define BUFF_SIZE 5
# define GNL_ERROR -1
# define GNL_END 0
# define GNL_OK 1
# define WIN_X 800
# define WIN_Y 600
# define HALFW 600
# define HALFH 300

# define EXIT			53
# define LEFT_CLICK		1
# define RIGHT_CLICK	2
# define SCROLL_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define NUM_1			18
# define NUM_2			19
# define NUM_3			20
# define NUM_4			21
# define NUM_5			23
# define NUM_6			22
# define NUM_7			26
# define NUM_8			28
# define NUM_9			25
# define NUM_0			29
# define PLUS			69
# define MOINS			78
# define SLASH			75
# define STAR			67
# define LEFT			123
# define RIGHT			124
# define DOWN			125
# define UP				126

typedef struct		s_img
{
	unsigned int	width;
	unsigned int	height;
	int				bpp;
	int				sizeline;
	int				endian;
	void			*img;
	void			*win;
	void			*mlx;
	char			*data;

	float		movex;
	float 		movey;
	int 		mouse_x;
	int 		mouse_y;
	int 		state;
	int 		nb_points;
	int 		nb_colonnes;
	int 		nb_lines;
	int 		**map;
	int 		player_x;
	int 		player_y;

}					t_img;


// Put a pixel on screen
void	mlx_pixel_put_to_image(void *img, int x, int y, unsigned long color)
{
	t_img	pic;
	int		i;

	pic.data = mlx_get_data_addr(img, &pic.bpp, &pic.sizeline, &pic.endian);
	i = x * 4 + y * pic.sizeline;
	if (x >= 0 && y >= 0 && x <= WIN_X && y <= WIN_Y)
	{
		pic.data[i] = color % 256;
		color /= 256;
		pic.data[i + 1] = color % 256;
		color /= 256;
		pic.data[i + 2] = color % 256;
		color /= 256;
		pic.data[i + 3] = 0;
		color /= 256;
	}
}

// Draw a line from x0,y0 to x1,y1
void 	draw_a_line(t_img *e,int x0,int y0,int x1,int y1,unsigned long color)
{
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  while (x0>=0){
  	mlx_pixel_put_to_image(e->img, x0, y0, color);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

// Draw a square box left upper corner is bx0,by0  right down corder is bx1,by1
void draw_a_box(t_img *e,int bx0,int by0,int bx1,int by1,unsigned long color){
	while (by0<by1){
		draw_a_line(e,bx0,by0,bx1,by0,color);
		by0++;
	}
}

//****GET NEXT LINE****//
int     ft_realloc(char **rest)
{
    char        *tmp;

    if (!(tmp = ft_strnew(ft_strlen(*rest))))
        return (0);
    tmp = ft_strcpy(tmp, *rest);
    ft_memdel((void **)rest);
    if (!(*rest = ft_strnew(ft_strlen(tmp) + BUFF_SIZE)))
        return (0);
    *rest = ft_strcpy(*rest, tmp);
    ft_memdel((void **)&tmp);
    tmp = NULL;
    return (1);
}

char    *ft_fill_line(char **line, char **str, char *rest)
{
    int i;

    i = 0;
    *line = ft_strnew(ft_strlen(*str));
    while ((*str)[i] && (*str)[i] != '\n')
    {
        (*line)[i] = (*str)[i];
        i++;
    }
    (*line)[i] = '\0';
    if ((*str)[i] == '\n')
    {
        i++;
        ft_memdel((void **)&rest);
        if (!(rest = ft_strdup(*str + i)))
            return (NULL);
    }
    else
    {
        if (!(rest = ft_strdup(*str + i)))
            return (NULL);
    }
    return (rest);
}

int     ft_free_rest(char **rest, char **str)
{
    ft_memdel((void **)rest);
    ft_memdel((void **)str);
    return (GNL_END);
}

int     get_next_line(const int fd, char **line)
{
    static char *rest;
    int         ret;
    char        buff[BUFF_SIZE + 1];
    char        *str;

    (rest == NULL) ? rest = ft_strnew(1) : 0;
    if (!(str = ft_strdup(rest)) || (fd < 0))
        return (GNL_ERROR);
    while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
    {
        buff[ret] = '\0';
        if (!(ft_realloc(&str)))
            return (GNL_ERROR);
        str = ft_strcat(str, buff);
        if (ft_memchr(buff, '\n', BUFF_SIZE))
            break ;
    }
    if (ret < 0)
        return (GNL_ERROR);
    rest = ft_fill_line(line, &str, rest);
    if (ret == 0 && ft_strcmp(str, rest) == 0)
        return (ft_free_rest(&rest, &str));
    ft_memdel((void **)&str);
    return (GNL_OK);
}
//****FIN GET NEXT LINE****//

// load the map file and place data in e->map Array (2 dimensional array)
void 	load_map_file(char *argv,t_img *e)
{
	int 	i;
	int 	j;
	char 	*line;
	int 	fd;
	char	**tab;
	

	e->nb_lines = 0;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		e->nb_colonnes = 0;
		tab=ft_strsplit(line,' ');
		while (tab[e->nb_colonnes])
		{
			e->nb_colonnes++;
			e->nb_points++;
		}
		free(line);
		e->nb_lines++;
	}
	close(fd);

	
	e->map = malloc(e->nb_lines * sizeof(int*));
	//i=0;
	//while (i < e->nb_lines){
	//e->map[i] = malloc(e->nb_colonnes * sizeof(int));
	//	i++;
	//}

	i = 0;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		j = 0;
		e->map[i] = malloc(e->nb_colonnes * sizeof(int));
		tab=ft_strsplit(line,' ');
		while (tab[j])
		{
			
			e->map[i][j]=atoi(tab[j]);
			printf("%d",e->map[i][j]);
			if (e->map[i][j]==9){
				e->player_x=j;
				e->player_y=i;
			}
			j++;
		}
		free(line);
		i++;
		printf("\n");
	}
	close(fd);
}

// Key Hook
int 	key_hook(int keycode, t_img *e)
{
	if (keycode == EXIT)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	if (keycode == UP)
		{

		}
	if (keycode == DOWN)
		{

		}
	if (keycode == LEFT)
		{

		}
	if (keycode == RIGHT)
		{

		}
	
return (0);
}

// Mouse hook
int		mouse_all(int keycode, int x, int y, t_img *e)
{
	

	e->mouse_x=x;
	e->mouse_y=y;
	e->state=0;
	
	if (keycode == SCROLL_UP)
	{
		
	}
	if (keycode == SCROLL_DOWN){
		
	}
	if (keycode == LEFT_CLICK){
		
	
	
	}
	return (0);
}

//Mouse maniplation
int		manipulate(int x, int y, t_img *e)
{
	
	return (0);
}

// Show the map on the top left corner of the scrren
void show_map(t_img *e)
{
	int i;
	int j;
	int color;
	j=0;
	while (j<e->nb_lines)
	{
	i=0;
		while (i<e->nb_colonnes)
		{
			color=0xFFFFFF;
			if (i==e->player_x && j==e->player_y)
				color=0xFF0000;
			if (e->map[j][i]!=0) {
				draw_a_box(e,10+i*10,25+j*10,i*10+14,29+j*10,color);
			}
			i++;
		}
	j++;
	}
}

void show_image (t_img *e)
{
	e->img = mlx_new_image(e->mlx, WIN_X, WIN_Y);

	// Draw a blue box for the sky
	draw_a_box(e,0,0,WIN_X,WIN_Y/2,0x2255CC);

	// Draw a brown box for the ground
	draw_a_box(e,0,WIN_Y/2+1,WIN_X,WIN_Y,0xAA4422);
	show_map(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0); 
	//mlx_destroy_image(e->mlx, e->img);
	mlx_string_put(e->mlx, e->win, 10, 5, 0x0FFFFFF, "Current Map");
	//mlx_string_put(e->mlx, e->win, 100, 30, 0x0FFFFFF, ft_itoa(e->iteration));
	//mlx_string_put(e->mlx, e->win, 110, 50, 0x0FFFFFF, ft_itoa(e->mouse_x));
	//mlx_string_put(e->mlx, e->win, 155, 50, 0x0FFFFFF, ft_itoa(e->mouse_y));
	//mlx_string_put(e->mlx, e->win, 10, 50, 0x0FFFFFF, "mouse x,y:");

}

int 	main(int argc, char **argv)
{	
	t_img	*e;
		if (!(e = (t_img*)malloc(sizeof(t_img))))
			printf("Erreur Malloc -> e");

		load_map_file(argv[1],e);

printf("\n- Player start X: %d \n",e->player_x);
printf("\n- Player start Y: %d \n",e->player_y);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "WOLF 3D");
	show_image(e);
	//mlx_hook(e->win, 2, 3, key_hook,e);
	//mlx_hook(e->win, 4, 3, mouse_all, e);
	//mlx_hook(e->win, 6, 3, manipulate, e);
	mlx_loop(e->mlx);	
return(0);
}
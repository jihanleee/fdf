#include <mlx.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_point {
	int	x;
	int	y;
	int	z;
	int	connected;
}
void close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#include <fcntl.h>

void	readfile(char *pathname, char **file)
{
	int		count;
	int		n_rows;
	int		n_cols;
	char	buf[1];
	int		fd;

	fd = open("./test_maps/42.fdf", O_RDWR);
	count = 0;
	while (buf[0] != '\0')
	{
		read(fd, buf, 1);
		count++;
	}
	n_rows = count;
	while (1)
	{
	}
}


int	main(void)
{
	t_vars	vars;
	t_data	img;
	int		fd;
	int		i;
	int		j;
	char	**file;
	char	*line;


	while ()
	{
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	i = 0;
	my_mlx_pixel_put(&img, 0, i++, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx,vars.win, img.img, 10, 10);
	mlx_hook(vars.win, 17, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}

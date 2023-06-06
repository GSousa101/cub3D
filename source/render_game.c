#include "../include/cub3d.h"

int		map[15][20] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void	init_game(t_img *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, LENGHT, HEIGHT, "cub3D");
	img->img = mlx_new_image(img->mlx, LENGHT, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, int x0, int y0, int color, int l)
{
	int	x;
	int	y;

	x = x0;
	while (x < x0 + l)
	{
		y = y0;
		while (y < y0 + l)
		{
			pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

int	calc_square_sz(int nrows, int ncols, int length, int height)
{
	int	size;

	size = height / (ncols);
	if ((length / ncols) < size)
		size = length / (nrows);
	return (size);
}

void	render_map2d(t_img *img, int square_sz)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COLUMN)
		{
			if (map[i][j]  == 1)
				draw_square(img, i * square_sz, j * square_sz, 0xFF0000,
						calc_square_sz(ROW, COLUMN, LENGHT, HEIGHT));
			else
 				draw_square(img, i * square_sz, j * square_sz, 0xFFF000,
						calc_square_sz(ROW, COLUMN, LENGHT, HEIGHT));
			j++;
		}
		i++;
	}
}

void	draw_player(t_img *img, int x0, int y0, int l)
{
	int	x;
	int	y;

	x = x0;
	while (x < x0 + l)
	{
		y = y0;
		while (y < y0 + l)
		{
			pixel_put(img, x, y, 0x0FF000);
			y++;
		}
		x++;
	}
}

void	walk_up(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_y - 2) / 22;
	if (map[data->player.play_x/22][new_pos] != 1)
		data->player.play_y -= 2;
}

void	walk_right(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_y + 2) / 22;
	if (map[data->player.play_x/22][new_pos] != 1)
		data->player.play_y += 2;
}

void	walk_down(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_x + 2) / 22;
	if (map[new_pos][data->player.play_y/22] != 1)
		data->player.play_x += 2;
}

void	walk_left(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_x - 2) / 22;
	if (map[new_pos][data->player.play_y/22] != 1)
		data->player.play_x -= 2;
}

int	key_hooks(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->img.mlx, data->img.mlx_win);
		exit(0);
	}
	if (keycode == 126 || keycode == 13)
		walk_up(data);
	else if (keycode == 125 || keycode == 1)
		walk_right(data);
	else if (keycode == 123 || keycode == 0)
		walk_left(data);
	else if (keycode == 124 || keycode == 2)
		walk_down(data);
	// mlx_clear_window(data->img.mlx, data->img.mlx_win);
	render_map2d(&data->img, 22);
	draw_player(&data->img, data->player.play_x, data->player.play_y, 12);
	mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0,
			0);
	return (0);
}

void	render_game(void)
{
	int r;
	int c;
	t_data data;

	r = 15;
	c = 20;
	data.player.play_x = 30;
	data.player.play_y = 30;
	init_game(&data.img);
	render_map2d(&data.img, 22);
	draw_player(&data.img, data.player.play_x, data.player.play_y, 12);
	mlx_key_hook(data.img.mlx_win, key_hooks, &data);
	mlx_put_image_to_window(data.img.mlx, data.img.mlx_win, data.img.img, 0, 0);
	mlx_loop(data.img.mlx);
}
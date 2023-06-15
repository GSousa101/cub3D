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
				draw_square(img, i * square_sz, j * square_sz, 0xFF0000, 22);
			else
 				draw_square(img, i * square_sz, j * square_sz, 0xFFF000, 22);
			j++;
		}
		i++;
	}
} 

void	draw_player(t_img *img, t_player player, int l)
{
	int	x;
	int	y;
	int	x_pxl = 22 * player.play_x;
	int	y_pxl = 22 * player.play_y;

	x = x_pxl;
	while (x < x_pxl + l) //draw player square
	{
		y = y_pxl;
		while (y < y_pxl + l)
		{
			pixel_put(img, x, y, 0x0FF000);
			y++;
		}
		x++;
	}
	//draw direction point
	int	dirX_pxl = (player.play_x + player.dirX) * 22;
	int dirY_pxl = (player.play_y + player.dirY) * 22;
	pixel_put(img, dirX_pxl, dirY_pxl, 0x000FF0);
}

// readKeys();
//     //move forward if no wall in front of you
//     if (keyDown(SDLK_UP))
//     {
//       if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//     }
//     //move backwards if no wall behind you
//     if (keyDown(SDLK_DOWN))
//     {
//       if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//     }

void	walk_up(t_data *data)
{
	// int new_pos;

		data->player.play_x += data->player.dirX * data->player.speed;
		data->player.play_y += data->player.dirY * data->player.speed;
}

void	walk_down(t_data *data)
{
	// int new_pos;
	
		data->player.play_x -= data->player.dirX * data->player.speed;
		data->player.play_y -= data->player.dirY * data->player.speed;
}

void	walk_right(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_x + 2);
	if (map[new_pos][(int)data->player.play_y] != 1)
		data->player.play_x += 2;
}

void	walk_left(t_data *data)
{
	int new_pos;
	
	new_pos = (data->player.play_x - 2);
	if (map[new_pos][(int)data->player.play_y] != 1)
		data->player.play_x -= 2;
}

int	key_hooks(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->img.mlx, data->img.mlx_win);
		exit(0);
	}
	if (keycode == 65362 || keycode == 119)
		walk_up(data);
	else if (keycode == 65363 || keycode == 100)
		walk_right(data);
	else if (keycode == 65361 || keycode == 97)
		walk_left(data);
	else if (keycode == 65364 || keycode == 115)
		walk_down(data);
	// mlx_clear_window(data->img.mlx, data->img.mlx_win);
	render_map2d(&data->img, 22);
	draw_player(&data->img, data->player, 12);
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
	data.player.play_x = 5;
	data.player.play_y = 17;
	data.player.dirX = 1;
	data.player.dirY = 0;
	data.player.speed = 0.5;
	init_game(&data.img);
	render_map2d(&data.img, 22);
	draw_player(&data.img, data.player, 12);
	mlx_key_hook(data.img.mlx_win, key_hooks, &data);
	mlx_put_image_to_window(data.img.mlx, data.img.mlx_win, data.img.img, 0, 0);
	mlx_loop(data.img.mlx);
}
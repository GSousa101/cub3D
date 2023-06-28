/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 09:37:54 by fcaetano          #+#    #+#             */
/*   Updated: 2023/06/27 10:18:47 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == 65362 || keycode == 119)
		game->key.w_is_press = 1;
	if (keycode == 65364 || keycode == 115)
		game->key.s_is_press = 1;
	if (keycode == 65363)
		game->key.ra_is_press = 1;
	if (keycode == 65361)
		game->key.la_is_press = 1;
	if (keycode == 97)
		game->key.a_is_press = 1;
	if (keycode == 100)
		game->key.d_is_press = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	if (keycode == 65362 || keycode == 119)
		game->key.w_is_press = 0;
	if (keycode == 65364 || keycode == 115)
		game->key.s_is_press = 0;
	if (keycode == 65363 || keycode == 100)
		game->key.ra_is_press = 0;
	if (keycode == 65361 || keycode == 97)
		game->key.la_is_press = 0;
	return (0);
}

int	loop_hook(t_game *game)
{
	if (game->key.w_is_press || game->key.s_is_press
		|| game->key.ra_is_press || game->key.la_is_press)
	{
		if (game->key.w_is_press)
			walk_forward (game);
		if (game->key.s_is_press)
			walk_backward (game);
		if (game->key.ra_is_press)
			turn_right (&game->player);
		if (game->key.la_is_press)
			turn_left (&game->player);
	}
	//render_map3d(game);

    render_map2d(game, 22);
    render_player(&game->img, game->player, 9);

	mlx_put_image_to_window(game->img.ptr, game->img.win,
		game->img.img, 0, 0);
	return (0);
}

void	render_game(t_game *game)
{
	print_mtx(game);
	//render_map3d(game);

    render_map2d(game, 22);
    render_player(&game->img, game->player, 9);
	mlx_hook(game->img.win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->img.win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->img.win, 17, 0, close_window, game);
	mlx_loop_hook(game->img.ptr, loop_hook, game);
	mlx_put_image_to_window(game->img.ptr, game->img.win,
		game->img.img, 0, 0);
	mlx_loop(game->img.ptr);
}

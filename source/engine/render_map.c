#include "../../include/cub3d.h"

void	render_map2d(t_game *game, int square_sz)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.cols)
		{
			if (game->map.mtx_int[i][j] == 1)
				draw_square(&game->img, i * square_sz, j * square_sz,
					0xFF0000);
			else
				draw_square(&game->img, i * square_sz, j * square_sz,
					0xFFF000);
			j++;
		}
		i++;
	}
}

void	render_map3d(t_game *game)
{
	draw_background(*game);
	// load_textures(game);
	raycast(game);
}

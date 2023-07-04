/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusta <gusta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2023/07/04 17:07:31 by gusta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned long	tex_color(t_img tex, int tex_pos, int tex_hit_x)
{
	int	tex_y;
	int	*texture;

	texture = (int *) tex.addr;
	tex_y = (int)tex_pos & (tex.height - 1);
	return (texture[tex.height * tex_y + tex_hit_x]);
}

/*
* 1. Calculate the lowest pixel to draw
* 2. Calculate the highest pixel to draw
* 3. Draw the pixels
*/
t_img	def_tex(t_game *game, t_ray_info *ray)
{
	if (ray->side_hit)
	{
		if (looking_north(ray))
			return (game->texture.north);
		if (looking_south(ray))
			return (game->texture.south);
	}
	else
	{
		if (looking_east(ray))
			return (game->texture.east);
		if (looking_west(ray))
			return (game->texture.west);
	}
	return (game->texture.north);
}

/*
* 1. Calculate the lowest pixel to draw
* 2. Calculate the highest pixel to draw
* 3. Calculate the step to move in the texture
* 4. Calculate the initial position in the texture
* 5. Draw the pixels
*/
void	draw_x_line(t_game *game, t_ray_info *ray, int actual_ray, int line_height)
{
	int		draw_limits[2];
	double	step_tex;
	double	tex_pos;
	int		tex_hit_x;
	t_img	tex;

	tex = def_tex(game, ray);
	tex_hit_x = calc_tex_hit_x(game, ray, tex);
	draw_limits[0] = calc_lowest_pixel(line_height);
	draw_limits[1] = calc_highest_pixel(line_height);
	step_tex = 1.0 * tex.height / line_height;
	tex_pos = (draw_limits[0] - HEIGHT / 2 + line_height / 2) * step_tex;
	while (draw_limits[0] <= draw_limits[1])
	{
		tex_pos += step_tex;
		if (ray->side_hit == 1)
			pixel_put(&game->img, actual_ray, draw_limits[0],
				(tex_color(tex, tex_pos, tex_hit_x) >> 1) & 8355711);
		else
			pixel_put(&game->img, actual_ray, draw_limits[0],
				tex_color(tex, tex_pos, tex_hit_x));
		draw_limits[0]++;
	}
}

/*
* 1. Calculate the ray direction
* 2. Calculate the distance to the wall
* 3. Calculate the height of the wall
* 4. Calculate the lowest and highest pixel to fill in current stripe
* 5. Calculate the texture offset

*/
void	paint_walls(t_game *game)
{
	int			actual_ray;
	int			line_height;
	t_ray_info	ray;

	actual_ray = 0;
	while (actual_ray < LENGHT)
	{
		config_ray(game, &ray, actual_ray);
		line_height = HEIGHT / ray.dist_new_pov;
		draw_x_line(game, &ray, actual_ray, line_height);
		actual_ray++;
	}
}

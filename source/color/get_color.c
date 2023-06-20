/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavosousa <gustavosousa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2023/06/07 12:58:26 by gustavosous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_number(char **mtx, int r, int g, int b)
{
	if (mtx[0][0] == '-'
		|| mtx[1][0] == '-'
		|| mtx [2][0] == '-')
		return (0);
	if (ft_strncmp(mtx[0], ft_itoa(r), ft_strlen(mtx[0])))
		return (0);
	if (ft_strncmp(mtx[1], ft_itoa(g), ft_strlen(mtx[1])))
		return (0);
	if (ft_strncmp(mtx[2], ft_itoa(b), ft_strlen(mtx[2])))
		return (0);
	return (1);
}

void	invalid_rgb(char **mtx, t_game *game)
{
	free_matrix(mtx);
	exit_game("Number rgb not valid", game);
}

int	ft_count_line(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}

int	translate_rgb(char *rgb, t_game *game)
{
	int		r;
	int		g;
	int		b;
	int		c;
	char	**lonely;

	if (ft_count_words(rgb, ',') != 3)
		exit_game("Number rgb not valid", game);
	lonely = ft_split(rgb, ',');
	r = ft_atoi(lonely[0]);
	g = ft_atoi(lonely[1]);
	b = ft_atoi(lonely[2]);
	if (!is_valid_number(lonely, r, g, b))
		invalid_rgb(lonely, game);
	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	free_matrix(lonely);
	return (c);
}

void	get_color(t_game *game, char *line)
{
	char	*cardinal;
	char	**line_mtx;
	char	*arg;

	line_mtx = ft_split(line, ' ');
	cardinal = line_mtx[0];
	arg = line_mtx[1];
	if (is_ceiling(cardinal, game))
		game->texture.ceiling = translate_rgb(arg, game);
	else if (is_floor(cardinal, game))
		game->texture.floor = translate_rgb(arg, game);
	free_matrix(line_mtx);
}

int	is_color(char *line)
{
	if (ft_count_words(line, ',') != 3)
		return (0);
	return (1);
}

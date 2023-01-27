/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:19:40 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:49 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*ft_get_img(t_player *player, char *file_name)
{
	mlx_texture_t	*text;
	mlx_image_t		*img;
	char			*file_path;
	int				size;

	size = ft_strlen(player->sprite_path) + ft_strlen(file_name) + 13;
	file_path = ft_calloc(size, sizeof(char));
	ft_strlcpy(file_path, player->sprite_path, size);
	ft_strlcat(file_path, "sprites/", size);
	ft_strlcat(file_path, file_name, size);
	ft_strlcat(file_path, ".png", size);
	text = mlx_load_png(file_path);
	free(file_path);
	if (!text)
		ft_mlxerror(player);
	img = mlx_texture_to_image(player->mlx, text);
	if (!img)
		ft_mlxerror(player);
	return (img);
}

void	ft_render_background(t_player *player)
{
	mlx_image_t	*img;
	int			i;
	int			j;

	i = -1;
	while (player->map[++i])
	{
		j = -1;
		while (player->map[i][++j])
		{
			img = ft_get_img(player, ft_get_file_name(player->map[i][j]));
			if (mlx_image_to_window(player->mlx, img, j * RES, i * RES) < 0)
				ft_mlxerror(player);
		}
	}
}

void	ft_render_player(t_player *player)
{
	player->img_player = ft_get_img(player, ft_get_file_name('A'));
	if (mlx_image_to_window(player->mlx, player->img_player,
			player->x * RES, player->y * RES) < 0)
		ft_mlxerror(player);
}

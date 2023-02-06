/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:19:40 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/06 15:20:57 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_image_t	*ft_get_img(t_player *player, char *file_name)
{
	mlx_texture_t	*text;
	mlx_image_t		*img;
	char			*file_path;
	int				size;

	size = ft_strlen(player->sprite_path) + ft_strlen(file_name) + 13;
	file_path = ft_calloc(size, sizeof(char));
	if (!file_path)
		ft_terror(0, player);
	ft_strlcpy(file_path, player->sprite_path, size);
	ft_strlcat(file_path, "sprites/", size);
	ft_strlcat(file_path, file_name, size);
	ft_strlcat(file_path, ".png", size);
	text = mlx_load_png(file_path);
	free(file_path);
	if (!text)
		ft_mlxerror(player);
	img = mlx_texture_to_image(player->mlx, text);
	mlx_delete_texture(text);
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
			img->instances[0].z = 0;
		}
	}
}

void	ft_update_player_img(t_player *player)
{
	char	*file_name;
	int32_t	x;
	int32_t	y;

	x = player->x * RES;
	y = player->y * RES;
	if (player->img)
	{
		x = player->img->instances[0].x;
		y = player->img->instances[0].y;
		mlx_delete_image(player->mlx, player->img);
	}
	file_name = ft_get_dir_file_name(player, "Player", player->dir);
	player->img = ft_get_img(player, file_name);
	free(file_name);
	if (mlx_image_to_window(player->mlx, player->img, x, y) < 0)
		ft_mlxerror(player);
}

void	ft_init_player(t_player *player)
{
	player->all_collects = ft_count_c(player->map, 'C');
	player->collects = 0;
	player->moves = 0;
	player->dir = 1;
	player->speed = PLAYER_SPEED;
	player->frames = 0;
	player->wait = 0;
	player->end = 0;
	player->enemies = 0;
	player->x = ft_get_pos(player->map, 'P') % ft_strlen(player->map[0]);
	player->y = ft_get_pos(player->map, 'P') / ft_strlen(player->map[0]);
	player->img = 0;
	ft_update_player_img(player);
	player->img->instances[0].z = 2;
}

void	ft_render_counters(t_player *player)
{
	mlx_image_t	*shards_img;
	mlx_image_t	*player_img;
	char		*file_name;

	player->moves_ui = ft_calloc(sizeof(mlx_image_t *), 11);
	if (!player->moves_ui)
		ft_terror(0, player);
	ft_moves_ui(player);
	shards_img = ft_get_img(player, ft_get_file_name('S'));
	if (mlx_image_to_window(player->mlx, shards_img, 0, 0) < 0)
		ft_mlxerror(player);
	shards_img->instances[0].z = 1;
	player->collects_ui = ft_calloc(sizeof(mlx_image_t *),
			player->all_collects * 2 + 2);
	if (!player->collects_ui)
		ft_terror(0, player);
	ft_collects_ui(player);
	file_name = ft_get_dir_file_name(player, "Player", 1);
	player_img = ft_get_img(player, file_name);
	free(file_name);
	if (mlx_image_to_window(player->mlx, player_img, 0, (ft_count_c(player->map,
					0) / ft_strlen(player->map[0]) - 1) * RES) < 0)
		ft_mlxerror(player);
	player_img->instances[0].z = 1;
}

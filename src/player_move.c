/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:00:13 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/04 18:15:40 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_on_collect(t_player *player)
{
	mlx_image_t	*img;

	if (player->map[player->y][player->x] != 'C')
		return ;
	player->collects++;
	ft_collects_ui(player);
	player->map[player->y][player->x] = '0';
	img = ft_get_img(player, ft_get_file_name('0'));
	if (mlx_image_to_window(player->mlx, img,
			player->x * RES, player->y * RES) < 0)
		ft_mlxerror(player);
	img->instances[0].z = 1;
}

static void	ft_on_exit(t_player *player)
{
	if (player->map[player->y][player->x] != 'X')
		return ;
	if (player->collects >= player->all_collects)
		player->end = "win";
	else
		ft_printf("You haven't found all shards yet!\n");
}

void	ft_move(t_player *player, int x, int y)
{
	int	prev_dir;

	if (player->map[player->y + y][player->x + x] == '1' || player->end)
		return ;
	player->x += x;
	player->y += y;
	++player->moves;
	prev_dir = player->dir;
	player->dir = y + 1 + ft_to_power(x - 1, 2) + (x - 1);
	if (prev_dir != player->dir)
		ft_update_player_img(player);
	ft_moves_ui(player);
	ft_on_collect(player);
	ft_on_exit(player);
}

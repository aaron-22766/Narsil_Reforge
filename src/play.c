/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:41:06 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:45 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_on_collect(t_player *player)
{
	if (player->map[player->y][player->x] != 'C')
		return ;
	player->collects++;
	if (player->collects == player->all_collects)
		ft_printf("You have found all shards. Bring them to the anvil!\n");
	else if (player->collects == 1)
		ft_printf("You have found %i shard. Only %i more!\n",
			player->collects, player->all_collects - player->collects);
	else
		ft_printf("You have found %i shards. Only %i more!\n",
			player->collects, player->all_collects - player->collects);
	player->map[player->y][player->x] = '0';
	if (mlx_image_to_window(player->mlx, ft_get_img(player,
				ft_get_file_name('0')), player->x * RES, player->y * RES) < 0)
		ft_mlxerror(player);
	mlx_delete_image(player->mlx, player->img_player);
	player->img_player = ft_get_img(player, ft_get_file_name('A'));
	if (mlx_image_to_window(player->mlx, player->img_player,
			player->x * RES, player->y * RES) < 0)
		ft_mlxerror(player);
}

static void	ft_on_exit(t_player *player)
{
	if (player->map[player->y][player->x] != 'E')
		return ;
	if (player->collects >= player->all_collects)
	{
		ft_printf("\nAgorel vae, mellon nin! ");
		ft_printf("Aragorn was able to reforge the sword.\n\n");
		ft_terminate_free(player, 0);
	}
	else
		ft_printf("You haven't found all shards yet!\n");
}

static void	ft_move(t_player *player, int x, int y)
{
	if (player->map[player->y + y][player->x + x] == '1')
		return ;
	player->img_player->instances[0].x += x * RES;
	player->img_player->instances[0].y += y * RES;
	player->x += x;
	player->y += y;
	ft_printf("Moves: %i\n", ++player->moves);
	ft_on_collect(player);
	ft_on_exit(player);
}

static void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			ft_printf("\nYou closed the window using the ESC key.\n\n");
			ft_terminate_free(player, 0);
		}
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_move(player, 0, -1);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_move(player, 0, 1);
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_move(player, -1, 0);
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_move(player, 1, 0);
	}
}

void	ft_play(t_player *player)
{
	int	width;
	int	height;

	width = ft_strlen(player->map[0]) * RES;
	height = ft_count_c(player->map, 0) / ft_strlen(player->map[0]) * RES;
	player->mlx = mlx_init(width, height, "Narsil Reforge", true);
	if (!player->mlx)
		ft_mlxerror(player);
	ft_strrchr(player->sprite_path, '/')[1] = 0;
	ft_render_background(player);
	player->x = ft_get_pos(player->map, 'P') % ft_strlen(player->map[0]);
	player->y = ft_get_pos(player->map, 'P') / ft_strlen(player->map[0]);
	ft_render_player(player);
	player->moves = 0;
	player->collects = 0;
	player->all_collects = (unsigned int)ft_count_c(player->map, 'C');
	mlx_key_hook(player->mlx, &ft_keyhook, player);
	mlx_loop(player->mlx);
	ft_printf("\nYou closed the window.\n\n");
	ft_terminate_free(player, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:41:06 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/27 14:33:19 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_move_key(t_player *player, int x, int y)
{
	player->key_down = 1;
	ft_animate_player_move(player);
	if (player->img->instances[0].x == player->x * RES
		&& player->img->instances[0].y == player->y * RES)
		ft_move(player, x, y);
}

static void	ft_key_press(t_player *player)
{
	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("\nYou closed the window using the ESC key.\n\n");
		ft_terminate_free(player, 0);
	}
	else if (mlx_is_key_down(player->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(player->mlx, MLX_KEY_W))
		ft_move_key(player, 0, -1);
	else if (mlx_is_key_down(player->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(player->mlx, MLX_KEY_S))
		ft_move_key(player, 0, 1);
	else if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(player->mlx, MLX_KEY_A))
		ft_move_key(player, -1, 0);
	else if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(player->mlx, MLX_KEY_D))
		ft_move_key(player, 1, 0);
}

static void	ft_hook(void *param)
{
	t_player	*player;

	player = param;
	player->key_down = 0;
	ft_key_press(player);
	if (player->key_down)
		player->key_hold++;
	else
		player->key_hold = 0;
	if ((player->img->instances[0].x != player->x * RES
			|| player->img->instances[0].y != player->y * RES)
		&& player->key_down == 0)
		ft_animate_player_move(player);
	if (player->moves && ft_count_c(player->map, 'E') > 0 && !player->end)
		ft_enemies(player);
	if (player->end)
	{
		player->wait++;
		if (player->frames == END_ANI)
			player->frames = 0;
		player->frames++;
		if ((!ft_strncmp(player->end, "win", 3) && player->wait
				>= PLAYER_SPEED * 5) || !ft_strncmp(player->end, "death", 3))
			ft_end_animation(player);
	}
}

void	ft_play(t_player *player)
{
	player->mlx = mlx_init(ft_strlen(player->map[0]) * RES,
			ft_count_c(player->map, 0) / ft_strlen(player->map[0]) * RES,
			"so_long_bonus", true);
	if (!player->mlx)
		ft_mlxerror(player);
	ft_strrchr(player->sprite_path, '/')[1] = 0;
	ft_render_background(player);
	ft_init_player(player);
	if (ft_count_c(player->map, 'E') != 0)
		ft_init_enemies(player);
	ft_render_counters(player);
	mlx_loop_hook(player->mlx, &ft_hook, player);
	mlx_loop(player->mlx);
	ft_printf("\nYou closed the window.\n\n");
	ft_terminate_free(player, 0);
}

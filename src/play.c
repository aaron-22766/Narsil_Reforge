/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:41:06 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/14 10:42:28 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Narsil_Reforge.h"

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
	if (mlx_is_key_down(player->mlx, MLX_KEY_UP)
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
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT_SHIFT)
		&& player->img->instances[0].x % SPRINT_SPEED == 0
		&& player->img->instances[0].y % SPRINT_SPEED == 0)
		player->speed = SPRINT_SPEED;
	else
		player->speed = PLAYER_SPEED;
}

static void	ft_hook(void *param)
{
	t_player	*player;

	player = param;
	player->frames++;
	if (player->frames % (DISPLAY_FPS / GAME_FPS) != 0)
		return ;
	if (player->frames == (DISPLAY_FPS / GAME_FPS))
		player->frames = 0;
	player->key_down = 0;
	ft_key_press(player);
	if ((player->img->instances[0].x != player->x * RES
			|| player->img->instances[0].y != player->y * RES)
		&& player->key_down == 0)
		ft_animate_player_move(player);
	if (player->moves && ft_count_c(player->map, 'E') > 0 && !player->end)
		ft_enemies(player);
	ft_end_animation(player);
}

void	ft_play(t_player *player)
{
	player->mlx = mlx_init(ft_strlen(player->map[0]) * RES,
			ft_count_c(player->map, 0) / ft_strlen(player->map[0]) * RES,
			"Narsil_Reforge", true);
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

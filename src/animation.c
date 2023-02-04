/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:21:41 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/01 16:40:54 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_end_message(t_player *player)
{
	if (!ft_strncmp(player->end, "death", 5))
		ft_printf("\nAragorn died at the hand of a Nazgul!\n\n");
	else if (!ft_strncmp(player->end, "win", 3))
	{
		ft_printf("\nAgorel vae, mellon nin! ");
		ft_printf("Aragorn was able to reforge the sword.\n\n");
	}
	ft_terminate_free(player, 0);
}

void	ft_end_animation(t_player *player)
{
	char	*file_name;

	if (!player->end)
		return ;
	player->wait++;
	if (!((!ft_strncmp(player->end, "win", 3) && player->wait
				>= RES / PLAYER_SPEED) || !ft_strncmp(player->end, "death", 3)))
		return ;
	if (player->frames == END_ANI)
		ft_end_message(player);
	player->frames++;
	if (player->frames % (END_ANI / ANI_FRAMES) != 0)
		return ;
	file_name = ft_get_ani_file_name(player);
	mlx_delete_image(player->mlx, player->ani_img);
	player->ani_img = ft_get_img(player, file_name);
	free(file_name);
	if (mlx_image_to_window(player->mlx, player->ani_img, player->x * RES - RES,
			player->y * RES - RES) < 0)
		ft_mlxerror(player);
}

void	ft_animate_player_move(t_player *player)
{
	if (player->img->instances[0].x < player->x * RES)
		player->img->instances[0].x += player->speed;
	else if (player->img->instances[0].x > player->x * RES)
		player->img->instances[0].x -= player->speed;
	if (player->img->instances[0].y < player->y * RES)
		player->img->instances[0].y += player->speed;
	else if (player->img->instances[0].y > player->y * RES)
		player->img->instances[0].y -= player->speed;
}

void	ft_animate_enemy(t_player *player, t_enemy *enemy)
{
	mlx_instance_t	p_inst;
	mlx_instance_t	e_inst;

	if (enemy->img->instances[0].x < enemy->x * RES)
		enemy->img->instances[0].x += ENEMY_SPEED;
	else if (enemy->img->instances[0].x > enemy->x * RES)
		enemy->img->instances[0].x -= ENEMY_SPEED;
	if (enemy->img->instances[0].y < enemy->y * RES)
		enemy->img->instances[0].y += ENEMY_SPEED;
	else if (enemy->img->instances[0].y > enemy->y * RES)
		enemy->img->instances[0].y -= ENEMY_SPEED;
	p_inst = player->img->instances[0];
	e_inst = enemy->img->instances[0];
	if ((e_inst.y == p_inst.y && e_inst.x <= p_inst.x + RES / 2 - 4
			&& e_inst.x >= p_inst.x - RES / 2 + 4) || (e_inst.x == p_inst.x
			&& e_inst.y <= p_inst.y + RES -1 && e_inst.y >= p_inst.y - RES / 2))
		player->end = "death";
}

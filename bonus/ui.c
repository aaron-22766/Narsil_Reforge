/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:44:26 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/26 15:19:51 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_update_moves(t_player *player, int moves, int c)
{
	char	*file_name;
	int		x;
	int		y;

	if (moves < 10)
	{
		if (player->moves_ui[c])
			mlx_delete_image(player->mlx, player->moves_ui[c]);
		file_name = ft_itoa(moves);
		if (!file_name)
			ft_terror(0, player);
		player->moves_ui[c] = ft_get_img(player, file_name);
		free(file_name);
		x = RES + c + c * N_W;
		y = (ft_count_c(player->map, 0) / ft_strlen(player->map[0]) - 1)
			* RES + (RES - N_H) / 2;
		if (mlx_image_to_window(player->mlx, player->moves_ui[c], x, y) < 0)
			ft_mlxerror(player);
		player->moves_ui[c]->instances[0].z = 2;
	}
	else
	{
		ft_update_moves(player, moves / 10, c - 1);
		ft_update_moves(player, moves % 10, c);
	}
}

void	ft_moves_ui(t_player *player)
{
	ft_update_moves(player, player->moves, ft_count_digits(player->moves));
}

static void	ft_update_collects(t_player *player, int collects, int c)
{
	char	*file_name;

	if (collects < 10)
	{
		if (player->collects_ui[c])
			mlx_delete_image(player->mlx, player->collects_ui[c]);
		file_name = ft_itoa(collects);
		if (!file_name)
			ft_terror(0, player);
		player->collects_ui[c] = ft_get_img(player, file_name);
		free(file_name);
		if (mlx_image_to_window(player->mlx, player->collects_ui[c],
				RES + c + c * N_W, (RES - N_H) / 2) < 0)
			ft_mlxerror(player);
		player->collects_ui[c]->instances[0].z = 2;
	}
	else
	{
		ft_update_collects(player, collects / 10, c - 1);
		ft_update_collects(player, collects % 10, c);
	}
}

void	ft_collects_ui(t_player *player)
{
	int	power;
	int	cc;

	cc = ft_count_digits(player->collects);
	ft_update_collects(player, player->collects, cc);
	power = 0;
	while (power < ft_count_digits(player->all_collects) + 1)
	{
		if (player->collects == ft_to_power(10, power) - !player->collects)
		{
			ft_update_collects(player, player->all_collects, cc
				+ ft_count_digits(player->all_collects) + 2);
			if (player->collects_ui[cc + 1])
				mlx_delete_image(player->mlx, player->collects_ui[cc + 1]);
			player->collects_ui[cc + 1] = ft_get_img(player,
					ft_get_file_name('s'));
			if (mlx_image_to_window(player->mlx, player->collects_ui[cc + 1],
					RES + cc + 1 + (cc + 1) * N_W, (RES - N_H) / 2) < 0)
				ft_mlxerror(player);
			player->collects_ui[cc + 1]->instances[0].z = 2;
			break ;
		}
		power++;
	}
}

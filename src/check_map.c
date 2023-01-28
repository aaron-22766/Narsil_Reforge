/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:27:16 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/26 14:46:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_check_rect(t_player *player)
{
	int	i;

	i = 0;
	while (player->map[i])
	{
		if (ft_strlen(player->map[i]) <= 1)
			ft_ferror(10, player);
		if (ft_strlen(player->map[i]) != ft_strlen(player->map[0]))
			ft_ferror(11, player);
		i++;
	}
	if (i == 0)
		ft_ferror(20, player);
	if (ft_strlen(player->map[0]) < 3)
		ft_ferror(12, player);
	if (i < 3)
		ft_ferror(13, player);
}

static void	ft_check_components(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (player->map[i])
	{
		j = 0;
		while (player->map[i][j])
		{
			if (!ft_strchr("10CEPX", player->map[i][j]))
				ft_ferror(14, player);
			j++;
		}
		i++;
	}
	if (ft_count_c(player->map, 'C') == 0)
		ft_ferror(15, player);
	if (ft_count_c(player->map, 'X') != 1)
		ft_ferror(16, player);
	if (ft_count_c(player->map, 'P') != 1)
		ft_ferror(17, player);
}

static void	ft_check_walls(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (player->map[0][i])
	{
		if (player->map[0][i] != '1')
			ft_ferror(18, player);
		i++;
	}
	i = 0;
	while (player->map[i + 1])
	{
		if (player->map[i][0] != '1'
			|| player->map[i][ft_strlen(player->map[i]) - 1] != '1')
			ft_ferror(18, player);
		i++;
	}
	j = 0;
	while (player->map[i - 1][j])
	{
		if (player->map[i][j] != '1')
			ft_ferror(18, player);
		j++;
	}
}

static void	ft_check_size(t_player *player)
{
	char	answer;

	if (ft_strlen(player->map[0]) < 82 && (ft_count_c(player->map, 0)
			/ ft_strlen(player->map[0])) < 44)
		return ;
	ft_printf("\nALERT!\nMap is bigger than what the iMac can display! ");
	ft_printf("Play anyway? (y/N) ");
	scanf("%c", &answer);
	if (answer != 'y')
	{
		ft_printf("\n");
		ft_free_player(player);
		exit(0);
	}
}

void	ft_check_map(t_player *player)
{
	ft_check_rect(player);
	ft_check_components(player);
	ft_check_walls(player);
	ft_check_path(player);
	ft_check_size(player);
	ft_printf("\nHelp Aragorn find all the shards of Narsil!\n");
}

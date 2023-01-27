/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:25:25 by arabenst          #+#    #+#             */
/*   Updated: 2023/01/23 10:48:54 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_c(char **map, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	if (c == 0)
		return (i * j);
	return (count);
}

char	*ft_get_file_name(char c)
{
	char	*file_name;

	if (c == '1')
		file_name = "Wall";
	else if (c == '0')
		file_name = "Path";
	else if (c == 'P')
		file_name = "Path";
	else if (c == 'C')
		file_name = "Collectible";
	else if (c == 'E')
		file_name = "Exit";
	else if (c == 'A')
		file_name = "Player_r";
	else
		file_name = "miss";
	return (file_name);
}

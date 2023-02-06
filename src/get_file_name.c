/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:38:45 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/06 16:39:27 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*ft_get_file_name(char c)
{
	if (ft_strchr("0PE", c))
		return ("Path");
	if (c == '1')
		return ("Wall");
	else if (c == 'C')
		return ("Collectible");
	else if (c == 'X')
		return ("Exit");
	else if (c == 'S')
		return ("Shards");
	else if (c == 's')
		return ("slash");
	return ("miss");
}

char	*ft_get_dir_file_name(t_player *player, char *type, int dir)
{
	int		size;
	char	*dir_str;
	char	*file_name;

	size = ft_strlen(type) + 3;
	file_name = ft_calloc(size, sizeof(char));
	if (!file_name)
		ft_terror(0, player);
	ft_strlcpy(file_name, type, size);
	ft_strlcat(file_name, "_", size);
	dir_str = ft_substr("brfl", dir, 1);
	if (!dir_str)
	{
		free(file_name);
		ft_terror(0, player);
	}
	ft_strlcat(file_name, dir_str, size);
	free(dir_str);
	return (file_name);
}

char	*ft_get_ani_file_name(t_player *player)
{
	char	*frame_num;
	char	*file_name;
	int		size;
	int		frame;

	frame = player->frames / (END_ANI / ANI_FRAMES);
	size = ft_strlen(player->end) + ft_count_digits(frame) + 3;
	file_name = ft_calloc(size, sizeof(char));
	if (!file_name)
		ft_terror(0, player);
	ft_strlcpy(file_name, player->end, size);
	ft_strlcat(file_name, "_", size);
	frame_num = ft_itoa(frame);
	if (!frame_num)
	{
		free(file_name);
		ft_terror(0, player);
	}
	ft_strlcat(file_name, frame_num, size);
	free(frame_num);
	return (file_name);
}

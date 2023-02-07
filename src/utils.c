/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:25:25 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/07 14:53:36 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Narsil_Reforge.h"

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

int	ft_to_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	return (nb * ft_to_power(nb, power - 1));
}

int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

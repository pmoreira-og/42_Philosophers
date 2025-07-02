/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:29:16 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 14:02:34 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_array(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->array = malloc((data->ac - 1) * sizeof(int));
	if (!data->array)
		return (0);
	while (data->av[++i])
	{
		if (!get_value(&data->array[j++], data->av[i]))
			return (free(data->array), 0);
	}
	return (1);
}

int	parser(t_data *data)
{
	if (!get_array(data))
		return (0);
	if (data->must_eat)
		data->num_of_meals = data->array[4];
	return (1);
}

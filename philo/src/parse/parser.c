/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:29:16 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/18 11:45:55 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_array(t_data *data, char **av)
{
	if (!get_value(&data->n_philos, av[1]))
		return (0);
	if (!get_value(&data->die_t, av[2]))
		return (0);
	if (!get_value(&data->eat_t, av[3]))
		return (0);
	if (!get_value(&data->sleep_t, av[4]))
		return (0);
	if (data->must_eat)
	{
		if (!get_value(&data->num_of_meals, av[5]))
			return (0);
	}
	else
		data->num_of_meals = 0;
	data->think_t = 0;
	return (1);
}

int	parser(t_data *data, char **av)
{
	if (!get_array(data, av))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:27:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 15:07:18 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	if (ac == 6)
		data->must_eat = true;
	else
		data->must_eat = false;
	data->num_of_meals = -1;
	if (!parser(data))
		return (p_error(ERR_STX), 0);
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->data->array[0])
	{
		table->philos[i].id = i + 1;
		pthread_create(&table->philos[i].trd, NULL, routine, &table->philos[i]);
		pthread_join(table->philos[i].trd, NULL);
	}
	return (1);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*temp;

	temp = malloc(sizeof(t_table));
	if (!temp)
		return (merror("table"), NULL);
	memset(temp, 0, sizeof(t_table));
	temp->data = malloc(sizeof(t_data));
	if (!temp->data)
		return (merror("table:data"), free(temp), NULL);
	if (!init_data(temp->data, ac, av))
		return(free(temp->data), free(temp), NULL);
	temp->philos = malloc(sizeof(t_philo) * (temp->data->array[0] + 1));
	if (!temp->philos)
		return (merror("table:philos"), clean_table(temp), NULL);
	memset(temp->philos, 0, sizeof(t_philo) * (temp->data->array[0] + 1));
	init_philos(temp);
	return (temp);
}

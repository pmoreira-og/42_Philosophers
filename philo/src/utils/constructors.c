/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:27:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/15 11:13:51 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int ac, char **av)
{
	if (ac == 6)
		data->must_eat = true;
	else
		data->must_eat = false;
	data->num_of_meals = -1;
	if (!parser(data, av))
		return (p_error(ERR_STX), 0);
	return (1);
}

int	init_philos(t_table *table)
{
	unsigned int	i;
	t_philo			*temp;

	i = -1;
	temp = NULL;
	while (++i < table->data.n_philos)
	{
		temp = &table->philos[i];
		temp->c_meal = table->data.num_of_meals;
		temp->id = i + 1;
		pthread_mutex_init(&temp->l_fork.lock, NULL);
		if (i != table->data.n_philos)
			temp->r_fork = &table->philos[i + 1].l_fork;
		if (temp->id % 2 == 0)
			pthread_create(&temp->trd, NULL, routine, temp);
		else
			pthread_create(&temp->trd, NULL, routine_odd, temp);
		pthread_join(temp->trd, NULL);
	}
	return (1);
}

bool	init_table(t_table *ptr, int ac, char **av)
{
	memset(ptr, 0, sizeof(t_table));
	if (!init_data(&ptr->data, ac, av))
		return (false);
	ptr->philos = malloc(sizeof(t_philo) * (ptr->data.n_philos + 1));
	if (!ptr->philos)
		return (merror("table:philos"), false);
	memset(ptr->philos, 0, sizeof(t_philo) * (ptr->data.n_philos + 1));
	get_table(ptr);
	gettimeofday(&ptr->data.tv, NULL);
	pthread_mutex_init(&ptr->locked, NULL);
	return (true);
}

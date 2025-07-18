/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:27:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/18 12:12:18 by pmoreira         ###   ########.fr       */
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
	if (data->n_philos == 0)
	{
		p_error("Invalid number of philosophers. Must be at least one");
		return (0);
	}
	return (1);
}

void	kill_threads(t_table *table, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(table->philos[i].trd);
		i++;
	}
}

bool	init_trds(t_table *table)
{
	unsigned int	i;
	t_philo			*temp;
	int				status;

	i = 0;
	temp = NULL;
	status = 0;
	while (i < table->data.n_philos)
	{
		temp = &table->philos[i];
		if (i % 2 == 0)
			status = pthread_create(&temp->trd, NULL, routine, temp);
		else
			status = pthread_create(&temp->trd, NULL, routine, temp);
		if (status != 0)
			return (kill_threads(table, i), false);
		i++;
	}
	i = 0;
	waiter(table);
	while (i < table->data.n_philos)
		pthread_join(table->philos[i++].trd, NULL);
	return (true);
}

int	init_philos(t_table *table)
{
	unsigned int	i;
	t_philo			*temp;

	i = 0;
	temp = NULL;
	p_state(get_current_time(), 0, 0, true);
	while (i < table->data.n_philos)
	{
		temp = &table->philos[i];
		temp->id = i + 1;
		temp->data = &table->data;
		temp->last_meal = get_current_time();
		pthread_mutex_init(&temp->l_fork, NULL);
		pthread_mutex_init(&temp->locked, NULL);
		if (i != table->data.n_philos)
			temp->r_fork = &table->philos[i + 1].l_fork;
		if (i + 1 == table->data.n_philos)
			temp->r_fork = &table->philos[0].l_fork;
		i++;
	}
	if (!init_trds(table))
		return (0);
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

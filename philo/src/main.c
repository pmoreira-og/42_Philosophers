/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:32 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/23 14:13:57 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	memset, printf, malloc, free, write,
	usleep, gettimeofday, pthread_create,
	pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock,
	pthread_mutex_unlock
*/

bool	check_is_dead(t_philo *philo)
{
	ft_mutex(&philo->locked, LOCK);
	if ((get_current_time() - philo->last_meal) > philo->data->die_t)
		return (ft_mutex(&philo->locked, UNLOCK), true);
	ft_mutex(&philo->locked, UNLOCK);
	return (false);
}

void	waiter(t_table *table)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < table->data.n_philos)
		{
			if (check_is_dead(&table->philos[i]))
			{
				p_state(get_current_time(), table->philos[i].id, DIED, false);
				return (update_dead(table));
			}
			if (table->data.must_eat)
			{
				if (check_meals(table, &table->philos[i],
						table->data.num_of_meals))
					return (update_dead(table));
			}
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 != 0)
		get_a_rest(philo->data->eat_t * 0.5);
	while (1)
	{
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		if (!ft_think(philo))
			break ;
	}
	return (NULL);
}

t_table	*get_table(t_table *data)
{
	static t_table	*address;

	if (data)
	{
		address = data;
		return (NULL);
	}
	else
		return (address);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (p_error(ERR_ARG), 0);
	if (!init_table(&table, ac, av))
		return (1);
	if (table.data.must_eat && (table.data.num_of_meals == 0))
		return (free(table.philos), 0);
	if (!init_philos(&table))
		return (free(table.philos), 1);
	return (free(table.philos), 0);
}

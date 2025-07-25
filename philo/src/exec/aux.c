/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:19:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/23 14:32:36 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex(pthread_mutex_t *mutex, t_state request)
{
	if (mutex)
	{
		if (request == LOCK)
			pthread_mutex_lock(mutex);
		else if (request == UNLOCK)
			pthread_mutex_unlock(mutex);
		else
			return ;
	}
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	check_dead_table(void)
{
	t_table	*table;

	table = get_table(NULL);
	ft_mutex(&table->locked, LOCK);
	if (table->dead)
		return (ft_mutex(&table->locked, UNLOCK), true);
	return (ft_mutex(&table->locked, UNLOCK), false);
}

bool	check_meals(t_table *table, t_philo *philo, unsigned int meals)
{
	bool	result;

	result = false;
	ft_mutex(&philo->locked, LOCK);
	if (philo->c_meal >= meals && !philo->done)
	{
		ft_mutex(&table->locked, LOCK);
		philo->done = true;
		table->done_meals += 1;
		if (table->done_meals >= table->data.n_philos)
		{
			table->dead = true;
			result = true;
		}
		ft_mutex(&table->locked, UNLOCK);
	}
	ft_mutex(&philo->locked, UNLOCK);
	return (result);
}

void	update_dead(t_table *table)
{
	ft_mutex(&table->locked, LOCK);
	table->dead = true;
	ft_mutex(&table->locked, UNLOCK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:19:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/18 11:46:38 by pmoreira         ###   ########.fr       */
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

bool	check_meals(t_philo *philo, unsigned int meals)
{
	ft_mutex(&philo->locked, LOCK);
	if (philo->c_meal >= meals)
		return (ft_mutex(&philo->locked, UNLOCK), true);
	return (ft_mutex(&philo->locked, UNLOCK), false);
}

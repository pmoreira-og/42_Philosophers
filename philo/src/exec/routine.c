/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/15 11:14:22 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	long	current;

	current = get_current_time();
	lock_fork(&philo->l_fork);
	lock_fork(philo->r_fork);
	philo->last_meal = current;
	p_state(current, philo->id, EATING);
	unlock_fork(&philo->l_fork);
	unlock_fork(philo->r_fork);
}

bool	check_is_dead(t_philo *philo, long start, long current)
{
	t_table			*table;

	table = get_table(NULL);
	pthread_mutex_lock(&table->locked);
	if (table->dead)
		return (pthread_mutex_unlock(&table->locked), true);
	if ((current - start) > table->data.die_t)
	{
		table->dead = true;
		p_state(current, philo->id, DIED);
		return (pthread_mutex_unlock(&table->locked), true);
	}
	return (pthread_mutex_unlock(&table->locked), false);
}

// void	ft_think(t_philo *philo, unsigned int time)
// {
// 	p_state(get_current_time(), philo->id, THINKING);
// 	usleep(time);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/23 12:56:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		ft_mutex(&philo->l_fork, UNLOCK);
		ft_mutex(philo->r_fork, UNLOCK);
	}
	else
	{
		ft_mutex(philo->r_fork, UNLOCK);
		ft_mutex(&philo->l_fork, UNLOCK);
	}
}

bool	grab_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_mutex(&philo->l_fork, LOCK);
	else
		ft_mutex(philo->r_fork, LOCK);
	p_state(get_current_time(), philo->id, HAS_FORK, false);
	if (!philo->r_fork)
		return (ft_mutex(&philo->l_fork, UNLOCK), false);
	if (philo->id % 2 != 0)
		ft_mutex(philo->r_fork, LOCK);
	else
		ft_mutex(&philo->l_fork, LOCK);
	p_state(get_current_time(), philo->id, HAS_FORK, false);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (!grab_forks(philo))
		return (false);
	if (p_state(get_current_time(), philo->id, EATING, false))
	{
		ft_mutex(&philo->locked, LOCK);
		philo->last_meal = get_current_time();
		philo->c_meal += 1;
		ft_mutex(&philo->locked, UNLOCK);
	}
	else
		return (release_forks(philo), false);
	get_a_rest(philo->data->eat_t);
	release_forks(philo);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (p_state(get_current_time(), philo->id, SLEEPING, false))
		get_a_rest(philo->data->sleep_t);
	else
		return (false);
	return (true);
}

bool	ft_think(t_philo *philo)
{
	long	time;

	if (!p_state(get_current_time(), philo->id, THINKING, false))
		return (false);
	if (philo->data->n_philos % 2 == 0)
		return (true);
	time = 2 * philo->data->eat_t - philo->data->sleep_t;
	if (time < 0)
		time = 0;
	get_a_rest(time * 0.42);
	return (true);
}

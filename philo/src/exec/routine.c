/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/18 11:52:02 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	manage_forks(t_philo *philo, t_state request)
{
	if (philo)
	{
		if (request == LOCK)
		{
			if ((philo->id) % 3 == 0)
				ft_mutex(&philo->l_fork, LOCK);
			else
				ft_mutex(philo->r_fork, LOCK);
			if (!check_dead_table())
				p_state(get_current_time(), philo->id, HAS_FORK, false);
			if ((philo->id) % 3 == 0)
				ft_mutex(philo->r_fork, LOCK);
			else
				ft_mutex(&philo->l_fork, LOCK);
			if (!check_dead_table())
				p_state(get_current_time(), philo->id, HAS_FORK, false);
		}
		if (request == UNLOCK)
		{
			ft_mutex(&philo->l_fork, UNLOCK);
			ft_mutex(philo->r_fork, UNLOCK);
		}
	}
}

bool	ft_eat(t_philo *philo)
{
	manage_forks(philo, LOCK);
	if (!check_dead_table())
	{
		ft_mutex(&philo->locked, LOCK);
		philo->last_meal = get_current_time();
		p_state(get_current_time(), philo->id, EATING, false);
		philo->c_meal += 1;
		ft_mutex(&philo->locked, UNLOCK);
	}
	else
		return (manage_forks(philo, UNLOCK), false);
	usleep(philo->data->eat_t * 1000);
	manage_forks(philo, UNLOCK);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (!check_dead_table())
	{
		p_state(get_current_time(), philo->id, SLEEPING, false);
		usleep(philo->data->sleep_t * 1000);
	}
	else
		return (false);
	return (true);
}

bool	ft_think(t_philo *philo)
{
	if (!check_dead_table())
		p_state(get_current_time(), philo->id, THINKING, false);
	else
		return (false);
	return (true);
}

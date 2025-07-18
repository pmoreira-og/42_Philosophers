/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/18 15:18:10 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	release_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		ft_mutex(philo->r_fork, UNLOCK);
		ft_mutex(&philo->l_fork, UNLOCK);
	}
	else
	{
		ft_mutex(&philo->l_fork, UNLOCK);
		ft_mutex(philo->r_fork, UNLOCK);
	}
}

void	grab_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
		ft_mutex(&philo->l_fork, LOCK);
	else
		ft_mutex(philo->r_fork, LOCK);
	if (!check_dead_table())
		p_state(get_current_time(), philo->id, HAS_FORK, false);
	if ((philo->id - 1) % 2 == 0)
		ft_mutex(philo->r_fork, LOCK);
	else
		ft_mutex(&philo->l_fork, LOCK);
	if (!check_dead_table())
		p_state(get_current_time(), philo->id, HAS_FORK, false);
}

bool	ft_eat(t_philo *philo)
{
	grab_forks(philo);
	if (!check_dead_table())
	{
		ft_mutex(&philo->locked, LOCK);
		philo->last_meal = get_current_time();
		p_state(get_current_time(), philo->id, EATING, false);
		philo->c_meal += 1;
		ft_mutex(&philo->locked, UNLOCK);
	}
	else
		return (release_forks(philo), false);
	usleep(philo->data->eat_t * 1000);
	release_forks(philo);
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

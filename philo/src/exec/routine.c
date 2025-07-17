/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/17 15:49:00 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_eat(t_philo *philo)
{
	ft_mutex(&philo->l_fork, LOCK);
	p_state(get_current_time(), philo->id, HAS_FORK, false);
	ft_mutex(philo->r_fork, LOCK);
	p_state(get_current_time(), philo->id, HAS_FORK, false);
	if (!check_dead_table())
	{
		philo->last_meal = get_current_time();
		p_state(get_current_time(), philo->id, EATING, false);
		ft_mutex(&philo->locked, LOCK);
		philo->c_meal += 1;
		ft_mutex(&philo->locked, UNLOCK);
	}
	else
		return (false);
	usleep(philo->data->eat_t * 1000);
	ft_mutex(&philo->l_fork, UNLOCK);
	ft_mutex(philo->r_fork, UNLOCK);
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
	usleep(philo->data->think_t * 1000);
	return (true);
}

bool	check_is_dead(t_philo *philo, long current)
{
	t_table	*table;

	table = get_table(NULL);
	ft_mutex(&table->locked, LOCK);
	if (table->dead)
		return (ft_mutex(&table->locked, UNLOCK), true);
	if ((current - philo->last_meal) > table->data.die_t)
	{
		table->dead = true;
		return (ft_mutex(&table->locked, UNLOCK), true);
	}
	return (ft_mutex(&table->locked, UNLOCK), false);
}

void	waiter(t_table *table)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		while (i < table->data.n_philos)
		{
			usleep(100);
			if (table->data.must_eat)
			{
				if (check_meals(&table->philos[i], table->data.num_of_meals))
					return ;
			}
			if (check_is_dead(&table->philos[i], get_current_time()))
			{
				p_state(get_current_time(), table->philos[i].id, DIED, false);
				return ;
			}
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:32 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/15 11:07:39 by pmoreira         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*philo;
	long	start;

	start = get_current_time();
	philo = (t_philo *)arg;
	if (check_is_dead(philo, start, get_current_time()))
		return (NULL);
	ft_eat(philo);
	return (NULL);
}

void	*routine_odd(void *arg)
{
	t_philo	*philo;
	long	start;

	start = get_current_time();
	philo = (t_philo *) arg;
	if (check_is_dead(philo, start, get_current_time()))
		return (NULL);
	ft_eat(philo);
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
	init_philos(&table);
	return (free(table.philos), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:32 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/21 14:53:21 by pmoreira         ###   ########.fr       */
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

bool	check_is_dead(t_philo *philo, long current)
{
	t_table	*table;

	table = get_table(NULL);
	ft_mutex(&table->locked, LOCK);
	if (table->dead)
		return (ft_mutex(&table->locked, UNLOCK), true);
	ft_mutex(&philo->locked, LOCK);
	if ((current - philo->last_meal) >= table->data.die_t)
	{
		table->dead = true;
		ft_mutex(&philo->locked, UNLOCK);
		return (ft_mutex(&table->locked, UNLOCK), true);
	}
	ft_mutex(&philo->locked, UNLOCK);
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
			get_a_rest(100);
			if (check_is_dead(&table->philos[i], get_current_time()))
			{
				p_state(get_current_time(), table->philos[i].id, DIED, false);
				return ;
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

void print_philo(const t_philo *philo)
{
    printf("Philosopher ID: %u\n", philo->id);
    printf("  Number of meals eaten: %u\n", philo->c_meal);
    printf("  Last meal timestamp: %lld\n", philo->last_meal);
    printf("  Data pointer: %p\n", (void*)philo->data);
    printf("  Left fork mutex: %p\n", (void*)&philo->l_fork);
    printf("  Right fork mutex ptr: %p\n", (void*)philo->r_fork);
    if (philo->r_fork) {
        printf("    (Points to mutex at address: %p)\n", (void*)philo->r_fork);
    } else {
        printf("    (Right fork pointer is NULL)\n");
    }
    printf("  Locked mutex: %p\n", (void*)&philo->locked);
    printf("  Thread: %lu\n", (unsigned long)philo->trd);
    printf("\n");
}

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) arg;
// 	print_philo(philo);
// 	return (NULL);
// }

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

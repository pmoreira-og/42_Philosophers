/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:32 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/17 15:57:36 by pmoreira         ###   ########.fr       */
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

void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		usleep(philo->data->sleep_t);
		if (!ft_think(philo))
			break ;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if ((philo->id - 1) % 2 != 0)
			usleep(100);
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

void	print_philo(const t_philo *philo)
{
	t_table *table = get_table(NULL);

	ft_mutex(&table->locked, LOCK);
	printf("Philosopher ID: %u\n", philo->id);
	printf("  Number of meals eaten: %u\n", philo->c_meal);
	printf("  Last meal timestamp: %lld\n", philo->last_meal);
	printf("  Data pointer: %p\n", (void*)philo->data);
	printf("  Left fork mutex: %p\n", (void*)&philo->l_fork);
	printf("  Right fork mutex: %p\n", (void*)philo->r_fork);
	printf("  Locked mutex: %p\n", (void*)&philo->locked);
	printf("  Thread: %lu\n", (unsigned long)philo->trd);
	printf("\n");
	ft_mutex(&table->locked, UNLOCK);

}

void print_data(const t_data *data) {
    printf("t_data:\n");
    printf("  must_eat: %s\n", data->must_eat ? "true" : "false");
    printf("  tv (timeval): %ld sec, %ld usec\n", data->tv.tv_sec, data->tv.tv_usec);
    printf("  n_philos: %u\n", data->n_philos);
    printf("  num_of_meals: %u\n", data->num_of_meals);
    printf("  die_t: %u\n", data->die_t);
    printf("  eat_t: %u\n", data->eat_t);
    printf("  sleep_t: %u\n", data->sleep_t);
    printf("  think_t: %u\n", data->think_t);
    printf("\n");
}

void print_table(const t_table *table) {
    printf("Table:\n");
    printf("  dead: %s\n", table->dead ? "true" : "false");
    printf("  Locked mutex: %p\n", (void*)&table->locked);
    print_data(&table->data);
    printf("Philosophers:\n");
    for (unsigned int i = 0; i < table->data.n_philos; ++i) {
        print_philo(&table->philos[i]);
    }
}

void	*test_rt(void *arg)
{
	t_philo	*philo;

	// (void) arg;
	philo = (t_philo *) arg;
	print_philo(philo);
	return (NULL);
}
int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (p_error(ERR_ARG), 0);
	if (!init_table(&table, ac, av))
		return (1);
	if (!init_philos(&table))
		return (free(table.philos), 1);
	// print_table(&table);
	return (free(table.philos), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:12:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/15 10:38:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/// @brief 
/// @param die_t Time to Die (in milliseconds).
/// @param eat_t Time to Eat (in milliseconds).
/// @param sleep_t Time to Sleep (in milliseconds).
/// @param think_t Time to Think (in milliseconds).
typedef struct s_data
{
	bool				must_eat;
	struct timeval		tv;
	unsigned int		n_philos;
	unsigned int		num_of_meals;
	unsigned int		die_t;
	unsigned int		eat_t;
	unsigned int		sleep_t;
	unsigned int		think_t;
}	t_data;

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	HAS_FORK,
	DIED,
	LOCKED,
	UNLOCKED
}	t_state;

typedef struct s_fork
{
	t_state			status;
	pthread_mutex_t	lock;
}	t_fork;

/// @brief Philosopher struct.
/// @param trd Thread of the philosopher.
/// @param id Id of the philosopher.
/// @param c_meal Count of the meals.
/// @param last_meal Time of the last meal.
/// @param locked Mutex to lock the access to the philosopher.
typedef struct s_philo
{
	pthread_t		trd;
	unsigned int	id;
	unsigned int	c_meal;
	long long		last_meal;
	t_fork			l_fork;
	t_fork			*r_fork;
}	t_philo;

typedef struct s_table
{
	bool			dead;
	t_philo			*philos;
	t_data			data;
	pthread_mutex_t	locked;
}	t_table;

#endif
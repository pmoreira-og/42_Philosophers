/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:12:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 14:04:51 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	bool	must_eat;
	int		num_of_meals;
	int		ac;
	char	**av;
	int		*array;
}	t_data;

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	DIED
}	t_state;

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
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	locked;

}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	t_data	*data;
}	t_table;


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:50:59 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/24 11:31:38 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include "structs.h"
# define ERR_ARG ": Invalid number of arguments."
# define ERR_STX ": Invalid syntax of the arguments."
# define USAGE "USAGE: number_of_philosophers time_to_die time_to_eat "
# define USAGE2 "time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define DEF "\e[0m"
//* Parsing

int			ft_tolower(int c);
int			ft_isspace(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			get_value(unsigned int *ptr, char *s);
int			parser(t_data *data, char **av);
long int	ft_strtol(char *s, char **endptr, int base, int *flag);
size_t		ft_strlen(char *s);

//* Utils

bool		init_table(t_table *ptr, int ac, char **av);
void		p_error(char *msg);
bool		p_state(long long time, int id, t_state state, bool save);
t_table		*get_table(t_table *data);
long long	get_current_time(void);
bool		get_a_rest(long long sleep_t);

//*Exec

void		*routine(void *arg);
void		*routine_odd(void *arg);
void		ft_mutex(pthread_mutex_t *mutex, t_state request);
int			init_philos(t_table *table);
bool		check_dead_table(void);
void		update_dead(t_table *table);

//*Routine

bool		ft_eat(t_philo *philo);
bool		ft_think(t_philo *philo);
bool		ft_sleep(t_philo *philo);
void		waiter(t_table *table);
bool		check_meals(t_table *table, t_philo *philo, unsigned int meals);

#endif
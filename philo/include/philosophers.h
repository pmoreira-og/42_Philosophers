/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:50:59 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/21 10:18:02 by pmoreira         ###   ########.fr       */
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
# define ERR_ARG "Invalid number of arguments."
# define ERR_STX "Invalid syntax of the arguments."

//* Parsing

int			ft_tolower(int c);
int			ft_isspace(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			get_value(unsigned int *ptr, char *s);
int			parser(t_data *data, char **av);
long int	ft_strtol(char *s, char **endptr, int base, int *flag);

//* Utils

bool		init_table(t_table *ptr, int ac, char **av);
void		merror(char *msg);
void		p_error(char *msg);
void		p_state(long long time, int id, t_state state, bool save);
t_table		*get_table(t_table *data);
long long	get_current_time(void);

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
void		*test_rt(void *arg);
void print_philo(const t_philo *philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:50:59 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 15:55:24 by pmoreira         ###   ########.fr       */
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
long int	ft_strtol(char *s, char **endptr, int base, int *flag);
int			ft_tolower(int c);
int			ft_isspace(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			get_value(int *ptr, char *s);
int			parser(t_data *data);

//* Utils
void		init_data(t_data *data, int ac, char **av);
void		clean_data(t_data *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:19:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/14 15:10:02 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_fork(t_fork *data)
{
	if (data)
	{
		pthread_mutex_lock(&data->lock);
		data->status = LOCKED;
	}
}

void	unlock_fork(t_fork *data)
{
	if (data)
	{
		pthread_mutex_unlock(&data->lock);
		data->status = UNLOCKED;
	}
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

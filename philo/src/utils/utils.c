/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:09:48 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/23 11:42:05 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_error(char *msg)
{
	if (msg)
		printf("%s\n", msg);
}

char	*get_state(t_state state)
{
	if (state == EATING)
		return ("is eating");
	if (state == THINKING)
		return ("is thinking");
	if (state == SLEEPING)
		return ("is sleeping");
	if (state == DIED)
		return ("died");
	if (state == HAS_FORK)
		return ("has taken a fork");
	return ("");
}

void	color_print(long long time, int id, t_state state)
{
	if (state == DIED)
		printf(RED"%lld %d %s\n"DEF, time, id, get_state(state));
	if (state == THINKING)
		printf(BLU"%lld %d %s\n"DEF, time, id, get_state(state));
	if (state == HAS_FORK)
		printf(YEL"%lld %d %s\n"DEF, time, id, get_state(state));
	if (state == SLEEPING)
		printf(MAG"%lld %d %s\n"DEF, time, id, get_state(state));
	if (state == EATING)
		printf(GRN"%lld %d %s\n"DEF, time, id, get_state(state));
}

/// @brief Prints philosopher state.
bool	p_state(long long time, int id, t_state state, bool save)
{
	static long long		start;
	static t_table			*table;

	if (save)
	{
		table = get_table(NULL);
		start = time;
		return (true);
	}
	else
	{
		ft_mutex(&table->locked, LOCK);
		if (!table->dead)
			color_print(time - start, id, state);
		else
			return (ft_mutex(&table->locked, UNLOCK), false);
		ft_mutex(&table->locked, UNLOCK);
		return (true);
	}
}

bool	get_a_rest(long long sleep_t)
{
	long	t_start;
	long	curr_time;
	long	elapsed_time;

	if (sleep_t <= 0)
		return (true);
	t_start = get_current_time();
	elapsed_time = 0;
	while (elapsed_time < sleep_t)
	{
		usleep(1);
		curr_time = get_current_time();
		elapsed_time = curr_time - t_start;
		if (check_dead_table())
			return (false);
	}
	return (true);
}

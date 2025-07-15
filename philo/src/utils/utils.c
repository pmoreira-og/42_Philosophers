/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:09:48 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/15 10:13:20 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	merror(char *msg)
{
	if (msg)
		printf("Malloc:%s\n", msg);
}

void	p_error(char *msg)
{
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

/// @brief Prints philosopher state.
void	p_state(long time, int id, t_state state)
{
	printf("%ld %d %s\n", time, id, get_state(state));
}

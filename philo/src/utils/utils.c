/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:09:48 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 14:25:52 by pmoreira         ###   ########.fr       */
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

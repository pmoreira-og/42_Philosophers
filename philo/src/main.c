/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:32 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/30 13:13:54 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_error(char *msg)
{
	printf("%s\n", msg);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (p_error(ERR_ARG), 0);
	if (ac == 6)
		data.must_eat = true;
	init_data(&data, ac, av);
	if (!parser(&data))
		return (p_error(ERR_STX), 0);
	return (clean_data(&data), 0);
}

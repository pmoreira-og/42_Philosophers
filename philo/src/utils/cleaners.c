/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:46 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 14:23:05 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	if (table->data && table->data->array)
		free(table->data->array);
	if (table->data)
		free(table->data);
	if (table->philos)
		free(table->philos);
	free(table);
}

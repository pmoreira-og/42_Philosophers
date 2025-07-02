/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:21:02 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 13:29:52 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_isalpha(int c)
{
	int	is_lower;
	int	is_upper;

	is_lower = (c >= 'a' && c <= 'z');
	is_upper = (c >= 'A' && c <= 'Z');
	return (is_upper || is_lower);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	get_value(int *ptr, char *s)
{
	long int	value;
	int			flag;
	char		*endptr;

	value = ft_strtol(s, &endptr, 10, &flag);
	if (flag)
		return (0);
	if (*endptr)
		return (0);
	if (value > INT_MAX || value < 1)
		return (0);
	*ptr = (int) value;
	return (1);
}

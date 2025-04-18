/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:55:55 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/19 13:29:08 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->rules->start_time);
}

int	ft_isdigit(int a)
{
	return ((a >= '0' && a <= '9'));
}

int	numctl(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '-' || str[j] == '+')
			return (0);
		if (!ft_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}

size_t	ft_atoi(const char *str)
{
	int		isaret;
	size_t	basamak;
	int		i;

	isaret = 1;
	basamak = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isaret *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		basamak = basamak * 10 + (str[i] - '0');
		i++;
	}
	return (isaret * basamak);
}

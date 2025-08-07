/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:07:19 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/07 10:38:22 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_mss(t_philo *philo)
{
	long	t;
	struct timeval	tv;

	t = philo->rules->start_time;
	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000 + tv.tv_sec * 1000) - t);
}

int	avctl(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!(numctl(av[i])))
			return (printf("ERROR\n"), 0);
		i++;
	}
	if (ac == 6 || ac == 5)
	{
		if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
			return (printf("ERROR!!! -> The number of philosophers cannot \
be greater than 200 and less than 1.\n"), 0);
		if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
			return (printf("ERROR!!! -> Eating time, dying time or \
sleeping time should not be below 60.\n"), 0);
		return (1);
	}
	else
		return (printf("Wrong Argument İnput !\n"), 0);
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

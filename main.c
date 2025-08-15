/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:30:23 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/16 00:30:25 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
int	avctl(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!(numctl(av[i])) || av[1][0] == '0')
			return (printf("ERROR\n"), 0);
		i++;
	}
	if (ac == 6 || ac == 5)
	{
		if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
			return (printf("ERROR!!! -> The number of philosophers cannot \
be greater than 200 and less than 1.\n"),
				0);
		if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
			return (printf("ERROR!!! -> Eating time, dying time or \
sleeping time should not be below 60.\n"),
				0);
		if (ac == 6 && ft_atoi(av[5]) < 1)
			return (printf("The amount to eat cannot be less than 1\n"), 0);
	}
	else
		return (printf("Wrong Argument İnput !\n"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!avctl(ac, av))
		return (1);
	init_program(&rules, philos, forks, av);
	quit(&rules, forks, -1);
	return (0);
}

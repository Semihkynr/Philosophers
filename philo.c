/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:03 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/16 12:57:49 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void startphilo(t_philo *philo , char **av, int ac)
{
	philo->philos = ft_atoi(av[1]);
	philo->dietime = ft_atoi(av[2]);
	philo->eattime = ft_atoi(av[3]);
	philo->sleeptime = ft_atoi(av[4]);
	if(ac == 6)
		philo->musteat = ft_atoi(av[5]);
	else
		philo->musteat = -1;
}

int avctl(int ac, char **av)
{
	int i;
	i = 1;
	while (av[i])
	{
		if(!(numctl(av[i])))
			return(printf("ERROR\n"),0);
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
		return(1);
	}
	else
		return(printf("Wrong Argument İnput !\n"), 0);
}

int	main(int ac, char **av)
{
	if(!avctl(ac , av))
		return (0);
	printf("SATIR 30\n");
	t_philo *philo;
	philo = malloc(sizeof(t_philo));
	startphilo(philo , av , ac);
	free(philo);
	return(0);
}

//number_of_philosophers :: time_to_die :: time_to_eat :: time_to_sleep :: number_of_times_each_philosopher_must_eat
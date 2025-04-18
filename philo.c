/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:03 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/18 18:09:54 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	// t_philo *philo = (t_philo *)arg;
	// while (1)
	// {
	// 	// take_forks(philo);
	// 	// eat(philo);
	// 	// drop_forks(philo);
	// 	// sleep_and_think(philo);
	// }
	return(NULL);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	philo->rules->start_time = get_time();
	while (i < philo->rules->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while(i < philo->rules->philo_count)
	{
		printf("PHİLO %d oluştu\n" , philo[i].id);
		i++;
	}
}

void	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_mutex_init(&philo->rules->forks[i], NULL);
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].left_fork = &philo->rules->forks[i];
		philo[i].right_fork = &philo->rules->forks[(i + 1)
			% philo->rules->philo_count];
		i++;
	}
}

void	start_philo(t_philo *philo, char **av, int ac)
{
	philo->rules = malloc(sizeof(t_rules));
	philo->rules->philo_count = ft_atoi(av[1]);
	philo->rules->time_to_die = ft_atoi(av[2]);
	philo->rules->time_to_eat = ft_atoi(av[3]);
	philo->rules->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->rules->must_eat = ft_atoi(av[5]);
	else
		philo->rules->must_eat = -1;
	philo->rules->forks = malloc(sizeof(pthread_mutex_t)
			* philo->rules->philo_count);
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

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (!avctl(ac, av))
		return (0);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	start_philo(philo, av, ac);
	init_mutex(philo);
	create_threads(philo);
	free(philo->rules->forks);
	free(philo->rules);
	free(philo);
	return (0);
}

// number_of_philosophers :: time_to_die :: time_to_eat :: time_to_sleep :: number_of_times_each_philosopher_must_eat
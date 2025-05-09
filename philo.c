/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:03 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/23 12:40:49 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int i;

	while (1)
	{
		i = 0;
		while (i < philo->rules->philo_count)
		{
			if (get_time(&philo[i]) - philo[i].last_meal >= philo->rules->time_to_die)
			{
				printf("%lu %d died\n", get_time(&philo[i]), philo[i].id);
				exit(0);
			}
			i++;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}


void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	philo->rules->start_time = get_time(philo);
	while (i < philo->rules->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		usleep(100);
		i++;
	}
	pthread_t	monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor, philo);
	
	int j = 0;
	while (j < philo->rules->philo_count)
	{
		pthread_join(philo[j].thread, NULL);
		j++;
	}
	pthread_join(monitor_thread, NULL);

}

void	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].rules = philo[0].rules;
		philo[i].forks = philo[0].forks;
		philo[i].last_meal = get_time(&philo[i]);
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
	philo->forks = malloc(sizeof(pthread_mutex_t)
			* philo->rules->philo_count);
	philo->rules->start_time = 0;
	philo->rules->start_time = get_time(philo);
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
	free(philo->forks);
	free(philo->rules);
	free(philo);
	return (0);
}

// number_of_philosophers :: time_to_die :: time_to_eat :: time_to_sleep :: number_of_times_each_philosopher_must_eat
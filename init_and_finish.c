/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:29:30 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/19 10:57:42 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit(t_rules *rules, pthread_mutex_t *forks, int i)
{
	pthread_mutex_destroy(&rules->write);
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->dead);
	while (++i < rules->philos[0].philo_num)
		pthread_mutex_destroy(&forks[i]);
}

void	init_input(t_philo *philo, char **av)
{
	if (av[5])
		philo->eat_count = ft_atoi(av[5]);
	else
		philo->eat_count = -1;
	philo->sleep_time = ft_atoi(av[4]);
	philo->eat_time = ft_atoi(av[3]);
	philo->die_time = ft_atoi(av[2]);
	philo->philo_num = ft_atoi(av[1]);
}

void	init_philos(t_rules *rules, t_philo *philos, pthread_mutex_t *forks,
		char **av)
{
	size_t	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		init_input(&philos[i], av);
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].eating = 0;
		philos[i].id = i + 1;
		philos[i].time_meal = &rules->meal;
		philos[i].time_dead = &rules->dead;
		philos[i].time_write = &rules->write;
		philos[i].dead = &rules->is_dead;
		philos[i].meals_eaten = 0;
		philos[i].left = &forks[i];
		if (i == 0)
			philos[i].right = &forks[philos[i].philo_num - 1];
		else
			philos[i].right = &forks[i - 1];
	}
}

void	init_program(t_rules *rules, t_philo *philos, pthread_mutex_t *forks,
		char **av)
{
	size_t	i;

	pthread_mutex_init(&rules->write, NULL);
	pthread_mutex_init(&rules->meal, NULL);
	pthread_mutex_init(&rules->dead, NULL);
	rules->philos = philos;
	rules->is_dead = 0;
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&forks[i], NULL);
	init_philos(rules, philos, forks, av);
	thread_create(rules, -1);
}

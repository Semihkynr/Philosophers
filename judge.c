/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:30:44 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/19 10:57:40 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output(t_philo *philo, char *str)
{
	long	t;

	pthread_mutex_lock(philo->time_dead);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->time_dead);
		return ;
	}
	pthread_mutex_unlock(philo->time_dead);
	pthread_mutex_lock(philo->time_write);
	t = get_current_time() - philo->start_time;
	printf("%ld %d %s\n", t, philo->id, str);
	pthread_mutex_unlock(philo->time_write);
}

int	dead_philo(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->time_meal);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->time_meal), 1);
	pthread_mutex_unlock(philo->time_meal);
	return (0);
}

int	check_dead(t_philo *philos, int i)
{
	while (++i < philos[0].philo_num)
	{
		if (dead_philo(&philos[i], philos[i].die_time))
		{
			output(&philos[i], "died");
			pthread_mutex_lock(philos[0].time_dead);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].time_dead);
			return (1);
		}
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos, int i, int finish)
{
	if (philos[0].eat_count == -1)
		return (0);
	while (++i < philos[0].philo_num)
	{
		pthread_mutex_lock(philos[i].time_meal);
		if (philos[i].meals_eaten >= philos[i].eat_count)
			finish++;
		pthread_mutex_unlock(philos[i].time_meal);
	}
	if (finish == philos[0].philo_num)
	{
		pthread_mutex_lock(philos[0].time_dead);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].time_dead);
		return (1);
	}
	return (0);
}

void	*judge(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_all_ate(philos, -1, 0) == 1 || check_dead(philos, -1) == 1)
			break ;
	return (pointer);
}

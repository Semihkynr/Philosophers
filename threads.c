/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:52 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/16 00:35:45 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	output(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	output(philo, "has taken a fork");
	if (philo->philo_num == 1)
	{
		ft_usleep(philo->die_time);
		pthread_mutex_unlock(philo->right);
		return ;
	}
	pthread_mutex_lock(philo->left);
	output(philo, "has taken a fork");
	philo->eating = 1;
	output(philo, "is eating");
	pthread_mutex_lock(philo->time_meal);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->time_meal);
	ft_usleep(philo->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	sleeping(t_philo *philo)
{
	output(philo, "is sleeping");
	ft_usleep(philo->sleep_time);
}

void	*life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(p->time_dead);
		if (*p->dead == 1)
		{
			pthread_mutex_unlock(p->time_dead);
			break ;
		}
		pthread_mutex_unlock(p->time_dead);
		think(p);
		eat(p);
		sleeping(p);
	}
	return (philo);
}

int	thread_create(t_rules *rules, int i)
{
	pthread_t	observer;

	pthread_create(&observer, NULL, &judge, rules->philos);
	while (++i < rules->philos[0].philo_num)
		pthread_create(&rules->philos[i].thread, NULL, &life,
			&rules->philos[i]);
	i = -1;
	pthread_join(observer, NULL);
	while (++i < rules->philos[0].philo_num)
		pthread_join(rules->philos[i].thread, NULL);
	return (0);
}

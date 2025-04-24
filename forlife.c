/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forlife.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:01:46 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/23 12:39:55 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void printer(t_philo *philo ,int msg)
{
	if(msg == 1)
		printf("%lu %d has taken a fork\n", get_time(philo) ,philo->id );
    if(msg == 2)
		printf("%lu %d has given a fork\n", get_time(philo) ,philo->id );
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->rules->philo_count]);
		printer(philo, 1);
		pthread_mutex_lock(&philo->forks[philo->id]);
		printer(philo, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		printer(philo, 1);
		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->rules->philo_count]);
		printer(philo, 1);
	}
}

 void	eat(t_philo *philo)
 {
    unsigned long now;
    now = get_time(philo);
    philo->eaten++;
    printf("%lu %d is eating\n", now, philo->id);
    philo->last_meal = now;
    usleep(philo->rules->time_to_eat);
}

void	drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->forks[philo->id]);
    printer(philo , 2);
    pthread_mutex_unlock(&philo->forks[(philo->id + 1 ) % philo->rules->philo_count]);
    printer(philo , 2);
}
void sleep_and_think(t_philo *philo)
{
    printf("%lu %d is sleeping\n", get_time(philo), philo->id);
    usleep(philo->rules->time_to_sleep);
    printf("%lu %d is thinking\n", get_time(philo), philo->id);
}
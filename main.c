/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:07:17 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/07 16:23:39 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		pthread_mutex_lock(&philo->eaten);
		if (philo->rules->must_eat != -1
			&& philo->eat_count >= data->must_eat * data->number_philo)
		{
			pthread_mutex_lock(&data->write_mutex);
			return ;
		}
		data->cont = (i % data->number_philo);
		if (get_mss(data) - data->philos[data->cont].last_eat
			>= data->time_to_die)
		{
			pthread_mutex_lock(&data->write_mutex);
			printf("%lu %d died\n", get_mss(data), data->cont + 1);
			return ;
		}
		pthread_mutex_unlock(&data->is_eat);
		i++;
		usleep(100);
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
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		usleep(100);
		i++;
	}
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
	create_threads(philo);
}

void	start_philo(t_rules *rules, char **av, int ac)
{
	
}

int main(int ac, char **av)
{
    if(!avctl(ac,av))
        return(1);
	
    t_rules *rules;
	rules = (t_rules *)malloc(sizeof(t_rules));
    start_philo(rules);
    return(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:57:38 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/13 17:54:51 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroydetach(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&rules->is_eat);
	pthread_mutex_destroy(&rules->mutex);
	while (i < rules->num)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	i = 0;
	while (i < rules->num)
	{
		pthread_detach(rules->philos[i].thread);
		i++;
	}
	free(rules->forks);
	free(rules->philos);
	free(rules);
}

void	go_sleep(t_philo *p, long time)
{
	long	dest_time;

	dest_time = set_time(p->data) + time;
	while (set_time(p->data) < dest_time)
		usleep(100);
}

// void	ft_usleep(size_t mls)
// {
// 	size_t	start;

// 	start = get_time_ms();
// 	while (get_time_ms() - start < mls)
// 		usleep(500);
// }

// long	get_time_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// long	set_time(t_rules *rules)
// {
// 	return (get_time_ms() - rules->start_time);
// }
long	set_time(t_rules *rules)
{
	long	t;

	t = rules->start_time;
	gettimeofday(&rules->tv, NULL);
	return ((rules->tv.tv_usec / 1000 + rules->tv.tv_sec * 1000) - t);
}

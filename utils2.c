/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:57:38 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/13 17:17:57 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *p, long time)
{
	long	dest_time;

	dest_time = set_time(p->data) + time;
	while (set_time(p->data) < dest_time)
		ft_usleep(100);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < mls)
		usleep(100);
}

long get_time_ms(void)
{
    struct timeval tv;
	
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long set_time(t_rules *rules)
{
    return (get_time_ms() - rules->start_time);
}

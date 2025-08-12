/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:07:17 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/12 18:04:26 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < mls)
		usleep(10);
}

void	writes(t_philo *p, int num)
{
	if (num == 0)
	{
		pthread_mutex_lock(&p->data->mutex);
		printf("%lu %d has taken a fork\n", set_time(p->data), p->id + 1);
		pthread_mutex_unlock(&p->data->mutex);
	}
	else if (num == 1)
	{
		pthread_mutex_lock(&p->data->mutex);
		printf("%lu %d is sleeping\n", set_time(p->data), p->id + 1);
		pthread_mutex_unlock(&p->data->mutex);
	}
	else if (num == 2)
	{
		pthread_mutex_lock(&p->data->mutex);
		printf("%lu %d is thinking\n", set_time(p->data), p->id + 1);
		pthread_mutex_unlock(&p->data->mutex);
	}
	else if (num == 3)
	{
		pthread_mutex_lock(&p->data->mutex);
		printf("%lu %d is eating\n", set_time(p->data), p->id + 1);
		pthread_mutex_unlock(&p->data->mutex);
	}
}

void	go_sleep(t_philo *p, long time)
{
	long	dest_time;

	dest_time = set_time(p->data) + time;
	while (set_time(p->data) < dest_time)
		ft_usleep(100);
}


void	main_thread(t_rules *rules)
{
	int	i;

	i = 1;
	while (1)
	{
		pthread_mutex_lock(&rules->is_eat);
		if (rules->must_eat != -1
			&& rules->eat_count >= rules->must_eat * rules->num)
		{
			pthread_mutex_lock(&rules->mutex);
			return ;
		}
		rules->cont = (i % rules->num);
		if (set_time(rules) - rules->philos[rules->cont].last_eat
			>= rules->time_to_die)
		{
			pthread_mutex_lock(&rules->mutex);
			printf("%lu %d died\n", set_time(rules), rules->cont + 1);
			return ;
		}
		pthread_mutex_unlock(&rules->is_eat);
		i++;
		ft_usleep(10);
	}
}

void	*life(void *philo)
{
	t_philo	*p;

	p = (t_philo*)philo;
	while (1)
	{
		pthread_mutex_lock(&p->data->forks[p->id]);
		writes(p, 0);
		pthread_mutex_lock(&p->data->forks[(p->id + 1)
			% p->data->num]);
		writes(p, 0);
		writes(p, 3);
		pthread_mutex_lock(&p->data->is_eat);
		p->data->eat_count++;
		p->last_eat = set_time(p->data);
		pthread_mutex_unlock(&p->data->is_eat);
		go_sleep(p, p->data->time_to_eat);
		writes(p, 1);
		pthread_mutex_unlock(&p->data->forks[p->id]);
		pthread_mutex_unlock(&p->data->forks[(p->id + 1)
			% p->data->num]);
		go_sleep(p, p->data->time_to_sleep);
		writes(p, 2);
	}
	return (NULL);
}

int	thread_create(t_rules *rules)
{
	int	i;
	i = -1;
	while (++i < rules->num)
	{
		rules->philos[i].last_eat = set_time(rules);
		rules->philos[i].dead = false;
		rules->philos[i].id = i;
		rules->philos[i].data = rules;
		pthread_create(&rules->philos[i].thread, NULL, life,
			&rules->philos[i]);
		ft_usleep(1);
	}
	return (0);
}

void	start_philo(t_rules *rules, char **av)
{
	int i;
	
	i = -1;
	rules->eat_count = 0;
	rules->must_eat = -1;
	rules->start_time = 0;
	rules->num = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	rules->start_time = set_time(rules);
	if(av[5])
		rules->must_eat = ft_atoi(av[5]);
	pthread_mutex_init(&rules->is_eat, NULL);
	pthread_mutex_init(&rules->mutex, NULL);
	rules->philos = malloc(sizeof(t_philo) * rules->num);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num);
	while (++i < rules->num)
		pthread_mutex_init(&rules->forks[i], NULL);
	thread_create(rules);
}

int main(int ac, char **av)
{
    if(!avctl(ac,av))
        return(1);
	
    t_rules *rules;
	rules = (t_rules *)malloc(sizeof(t_rules));
    start_philo(rules, av);
	main_thread(rules);
    return(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:07:17 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/13 17:18:46 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		for_out(p, 0);
		pthread_mutex_lock(&p->data->forks[(p->id + 1)
			% p->data->num]);
		for_out(p, 0);
		for_out(p, 3);
		pthread_mutex_lock(&p->data->is_eat);
		p->data->eat_count++;
		p->last_eat = set_time(p->data);
		pthread_mutex_unlock(&p->data->is_eat);
		go_sleep(p, p->data->time_to_eat);
		for_out(p, 1);
		pthread_mutex_unlock(&p->data->forks[p->id]);
		pthread_mutex_unlock(&p->data->forks[(p->id + 1)
			% p->data->num]);
		go_sleep(p, p->data->time_to_sleep);
		for_out(p, 2);
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
	rules->start_time = get_time_ms();
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

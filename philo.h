/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:08 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/19 15:11:55 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>   // malloc
# include <string.h>   // memset
# include <sys/time.h> // get time of day
# include <unistd.h>

typedef struct s_rules
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	t_rules			*rules;
}					t_philo;

// code

void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	drop_forks(t_philo *philo);
void sleep_and_think(t_philo *philo);

size_t				ft_atoi(const char *str);
int					numctl(char *str);
long	get_time(t_philo *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:19 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/19 10:57:30 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 210

typedef struct s_philo
{
	size_t			die_time;
	size_t			last_meal;
	size_t			start_time;
	size_t			sleep_time;
	size_t			eat_time;
	int				meals_eaten;
	int				eating;
	int				id;
	int				philo_num;
	int				eat_count;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*time_meal;
	pthread_mutex_t	*time_dead;
	pthread_mutex_t	*time_write;
}					t_philo;

typedef struct s_rules
{
	t_philo			*philos;
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	int				is_dead;
}					t_rules;

void				quit(t_rules *rules, pthread_mutex_t *forks, int i);
void				output(t_philo *philo, char *str);
void				init_program(t_rules *rules, t_philo *philos,
						pthread_mutex_t *forks, char **av);
size_t				get_current_time(void);
void				ft_usleep(size_t ms);
int					thread_create(t_rules *rules, int i);
void				*judge(void *pointer);
size_t				ft_atoi(const char *str);

#endif
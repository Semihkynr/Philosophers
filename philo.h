/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:24:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/13 17:42:29 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	bool			dead;
	int				id;
	struct s_rules	*data;
	pthread_t		thread;
	long			last_eat;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	is_eat;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	struct timeval	tv;
	int				num;
	int				cont;
	int				eat_count;
	int				must_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	t_philo			*philos;
}					t_rules;

void				go_sleep(t_philo *p, long time);
// void				usleep(size_t mls);
// long				get_time_ms(void);
void				destroydetach(t_rules *rules);
long				set_time(t_rules *rules);
void				for_out(t_philo *p, int num);
size_t				ft_atoi(const char *str);
int					numctl(char *str);
int					avctl(int ac, char **av);

#endif
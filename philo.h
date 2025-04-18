/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:08 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/18 17:05:03 by skaynar          ###   ########.fr       */
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
	pthread_mutex_t	*forks;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long			last_meal;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

// code

// utils
size_t				ft_atoi(const char *str);
int					numctl(char *str);

#endif

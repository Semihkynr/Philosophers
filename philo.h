#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>   // malloc
# include <sys/time.h> // get time of day
# include <unistd.h>

int	avctl(int ac, char **av);
int	ft_isdigit(int a);
int	numctl(char *str);
size_t	ft_atoi(const char *str);

typedef struct s_philo
{
	bool			dead;
	int				id;
	struct s_list	*data;
	pthread_t		thread;
	long			last_eat;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	is_eat;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
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


#endif
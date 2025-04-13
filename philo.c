/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:03 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/14 00:43:02 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int avctl(int ac, char **av)
{
	if (ac == 6 || ac == 5)
	{
		if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
			return (printf("ERROR!!! -> The number of philosophers cannot \
be greater than 200 and less than 1.\n"), 0);
		if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
			return (printf("ERROR!!! -> Eating time, dying time or \
sleeping time should not be below 60.\n"), 0);
		return(1);
	}
	else
		return(printf("Wrong Argument İnput !\n"), 0);
}
int	main(int ac, char **av)
{
	//void fonksiyon ile tüm struck tanımları 0 a eşitlenecek mallocla yer açılcak listeye
	if(!avctl(ac , av))
		return (0);
	printf("SATIR 30\n");

	return(0);
}

//number_of_philosophers :: time_to_die :: time_to_eat :: time_to_sleep :: number_of_times_each_philosopher_must_eat
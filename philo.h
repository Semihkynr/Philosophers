/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:56:08 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/16 12:56:38 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // malloc
#include <sys/time.h> // get time of day 
#include <pthread.h>

typedef struct s_philo
{
    int     philos;
    int     dietime;
    int     eattime;
    int     sleeptime;
    int     musteat;
}               t_philo;


//code 

// utils
size_t	ft_atoi(const char *str);
int	numctl(char *str);

#endif

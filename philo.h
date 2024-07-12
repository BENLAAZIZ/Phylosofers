#ifndef PHILO_H
# define PHILO_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>



typedef struct s_table
{
	long	philo_n;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_limit_meals; //
	long	start_sum;
}			t_table;



void	check_pars(t_table *tab, char **argv);

#endif
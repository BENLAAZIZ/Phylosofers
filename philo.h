#ifndef PHILO_H
# define PHILO_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>



typedef struct s_table
{
	int	philo_n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_limit_meals;
	int	start_sum;
}			t_table;

typedef struct s_phelo
{
	int	id_philo;
}			t_phelo;



int		check_pars(t_table *tab, char **argv);
char	*ft_strtrim(char const *s1, char const *set);

#endif
#ifndef PHILO_H
# define PHILO_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_data	t_data;

typedef struct s_philo
{
	int			philo_id;
	int			nbr_meals_eat;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	pthread_t		philo_th;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_limit_meals;
	int				is_died;
	int				full_data;
	size_t			start;
	pthread_mutex_t	print_M;
	pthread_mutex_t	dead_M;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	eat_M;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

int		check_pars(t_data *data, char **argv);
char	*ft_strtrim(char const *s1, char const *set);
size_t	current_time();

#endif
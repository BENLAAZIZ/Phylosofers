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
	int			n_meal;
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
	size_t			start_time;
	size_t			start;
	size_t			start_sim;
	pthread_mutex_t	print_mutix;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

int		check_pars(t_data *data, char **argv);
char	*ft_strtrim(char const *s1, char const *set);
size_t	current_time();
void	*routine(void *philo_data);
void	*one_thread(void *philo_data);
void	ft_usleep(int time, t_data *data);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	initializ_philo(t_data *data);
int		ft_init_mutex(t_data *data);
int		simulation(t_data *data);
int		creat_thread(t_data *data);
int		is_philo_died(t_philo *philo);
int		philo_full(t_data *data);
void	monitor(t_data *data);
int		get_var(pthread_mutex_t *mutex, int *var);
int		set_var(pthread_mutex_t *mutex, int *var, int value);
void	free_data(t_data *data);
int		end_simulation(t_data *data);
void	ft_printf(t_philo *philo, char *string);



#endif
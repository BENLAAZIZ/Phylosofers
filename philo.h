/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:04:13 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/29 12:19:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			philo_id;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	int			n_meal;
	pthread_t	philo_th;
	t_data		*data;
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
	pthread_mutex_t	print_mutix;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

size_t	current_time(void);
int		check_pars(t_data *data, char **argv);
char	*ft_strtrim(char const *s1, char const *set);
void	*routine(void *philo_data);
void	*one_thread(void *philo_data);
void	ft_usleep(int time, t_data *data);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	initializ_philo(t_data *data);
int		ft_init_mutex(t_data *data);
int		is_philo_dead(t_philo *philo);
int		philo_full(t_data *data);
void	monitor(t_data *data);
int		get_var(pthread_mutex_t *mutex, int *var);
void	ft_printf(t_philo *philo, char *string);
int		ft_ptread_join(t_data *data);
int		destroy_simulation(t_data *data, int flag);
void	ft_error(int flag);

#endif
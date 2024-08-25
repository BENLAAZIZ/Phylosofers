/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/25 23:48:56 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void v()
{
	system("leaks philo");
}
//**********
//**CHECK**
//****************	
//********************

// static int	ft_init_mutex(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philo_n)
// 	{
// 		if (pthread_mutex_init(&(data->forks[i]), NULL))
// 			return (1);
// 		i++;
// 	}
// 	if (pthread_mutex_init(&data->meal, NULL))
// 		return (1);
// 	if (pthread_mutex_init(&data->print_M, NULL))
// 		return (1);
// 	return (0);
// }
int get_int(pthread_mutex_t *mutex, int *var)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int set_int(pthread_mutex_t *mutex, int *var, int value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
	return (0);
}


void	ft_usleep(int time, t_data *data)
{
	size_t	start;

	start = current_time();
	while (current_time() - start < (size_t)time)
	{
		if (get_int(&data->data_mutex, &data->is_died)
			|| get_int(&data->data_mutex, &data->full_data))
			return ;
		usleep(100);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->eat_M);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->eat_M);
	printf("%ld %d is eating\n", current_time() - philo->data->start, philo->philo_id);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", current_time() - philo->data->start, philo->philo_id);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", current_time() - philo->data->start, philo->philo_id);
}	


void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->philo_id % 2 == 0)
		ft_usleep(60, philo->data);
	while (!get_int(&philo->data->data_mutex, &philo->data->is_died)
		&& !get_int(&philo->data->data_mutex, &philo->data->full_data))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}


int	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].nbr_meals_eat = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_n;
		if (pthread_create(&data->philo[i].philo_th, NULL, &routine, &data->philo[i]))
			return (write(2, "Thread error\n", 13), 1);
		i++;
	}
	i = 0;
	while (i < data->philo_n)
	{
		pthread_join(data->philo[i].philo_th, NULL);
		i++;
	}
	return (0);
}


// int	mutex_init(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	if (pthread_mutex_init(&data->print_M, NULL))
// 		return (1);
// 	if (pthread_mutex_init(&data->data_mutex, NULL))
// 		return (pthread_mutex_destroy(&data->print_M), 1);
// 	while (++i < data->philo_n)
// 	{
// 		if (pthread_mutex_init(&data->forks[i], NULL))
// 			return (pthread_mutex_destroy(&data->print_M),
// 				pthread_mutex_destroy(&data->data_mutex), 1);
// 	}
// 	return (0);
// }

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_M);
	pthread_mutex_destroy(&data->data_mutex);
	while (i < data->philo_n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->philo)    
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

int	ft_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philo)
		return (write(2, "Malloc error\n", 13), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (write(2, "Malloc error\n", 13), free(data->philo), 1);
	if (pthread_mutex_init(&data->print_M, NULL))
		return (write(2, "Mutex error\n", 12), free_data(data), 1);
	if (pthread_mutex_init(&data->dead_M, NULL))
		return (write(2, "Mutex error\n", 12), free_data(data), 1);
	if (pthread_mutex_init(&data->eat_M, NULL))
		return (write(2, "Mutex error\n", 12), free_data(data), 1);
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write(2, "Mutex error\n", 12), free_data(data), 1);
		i++;
	}
	i = 0;
	if (creat_thread(data) == 1)
		return (free_data(data), 1);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid argument\n", 17), 1);
	if (check_pars(&data, argv) == 1)
		return (1);
	if (data.number_limit_meals == 0)
		return (0);
	if (ft_init(&data) == 1)
		return (1);
	return (0);
}

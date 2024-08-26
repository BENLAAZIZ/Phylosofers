/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:28:33 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/26 17:07:43 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, t_data *data)
{
	size_t	start_sim;

	start_sim = current_time();
	while (current_time() - start_sim < (size_t)time)
	{
		if (get_var(&data->data_mutex, &data->is_died)
			|| get_var(&data->data_mutex, &data->full_data))
			return ;
		usleep(100);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	printf("%ld %d has taken a fork\n", current_time() - philo->data->start_sim, philo->philo_id);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf("%ld %d has taken a fork\n", current_time() - philo->data->start_sim, philo->philo_id);
	// pthread_mutex_lock(&philo->data->eat_M);
	philo->last_meal = current_time();
	// pthread_mutex_unlock(&philo->data->eat_M);
	philo->nbr_meals_eat++;
	printf("%ld %d is eating\n", current_time() - philo->data->start_sim, philo->philo_id);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

// void	eating(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 	print_status(philo, "has taken a fork\n");
// 	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
// 	print_status(philo, "has taken a fork\n");
// 	pthread_mutex_lock(&philo->data->data_mutex);
// 	philo->last_meal = get_current_time();
// 	philo->nbr_meals_eat++;
// 	pthread_mutex_unlock(&philo->data->data_mutex);
// 	print_status(philo, "is eating\n");
// 	ft_usleep(philo->data->time_to_eat, philo->data);
// 	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
// 	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
// }

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", current_time() - philo->data->start_sim, philo->philo_id);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", current_time() - philo->data->start_sim, philo->philo_id);
}	

int start_sim_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].data->start_sim = current_time();
		if (pthread_create(&data->philo[i].philo_th, NULL, &routine, &data->philo[i]))
			return (write(2, "Thread error\n", 13), 1);
		i++;
	}
	return (0);
}

int	end_simulation(t_data *data) // destroy mutex 
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&data->print_mutix))
		return (1);
	if (pthread_mutex_destroy(&data->data_mutex))
		return (1);
	while (++i < data->philo_n)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1);
	}
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	return (0);
}



void	monitor(t_data *data)
{
	int	i;

	while (!get_var(&data->data_mutex, &data->full_data))
	{
		i = -1;
		while (++i < data->philo_n)
		{
			pthread_mutex_lock(&data->print_mutix);
			if (is_philo_died(&data->philo[i]))
			{
				if (!get_var(&data->data_mutex, &data->is_died))
					printf("%ld %d died\n", current_time()
						- data->start_sim, data->philo[i].philo_id);
				pthread_mutex_unlock(&data->print_mutix);
				set_var(&data->data_mutex, &data->is_died, 1);
			}
			pthread_mutex_unlock(&data->print_mutix);
		}
		if (get_var(&data->data_mutex, &data->is_died))
			break ;
		if (philo_full(data))
			break ;
	}
}

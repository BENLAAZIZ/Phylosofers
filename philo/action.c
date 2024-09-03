/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:33:24 by hben-laz          #+#    #+#             */
/*   Updated: 2024/09/01 12:07:21 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_philo *philo, char *string)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->is_died != 1 && philo->data->is_full != 1)
	{
		pthread_mutex_lock(&philo->data->print_mutix);
		printf("%ld	%d	%s", current_time() - philo->data->start_time,
			philo->philo_id, string);
		pthread_mutex_unlock(&philo->data->print_mutix);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_printf(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = current_time();
	philo->n_meal++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	ft_sleep(t_philo *philo)
{
	ft_printf(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_usleep(int time, t_data *data)
{
	size_t	start_time;

	start_time = current_time();
	while (current_time() - start_time < (size_t)time)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->is_died == 1 || data->is_full == 1)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->data_mutex);
		usleep(200);
	}
}

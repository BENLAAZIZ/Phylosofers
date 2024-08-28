/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:33:54 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/28 18:59:17 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_printf(t_philo *philo, char *string)
// {
// 	long	start_time;

// 	// pthread_mutex_lock(&philo->data->data_mutex);
// 	start_time = philo->data->start_time;
// 	// pthread_mutex_unlock(&philo->data->data_mutex);
// 	pthread_mutex_lock(&philo->data->print_mutix);
// 	if (!get_var(&philo->data->data_mutex, &philo->data->is_died)
// 		&& !get_var(&philo->data->data_mutex, &philo->data->full_data))
// 		printf("%ld	%d	%s", current_time() - start_time,
// 			philo->philo_id, string);
// 	pthread_mutex_unlock(&philo->data->print_mutix);
// }

void	ft_printf(t_philo *philo, char *string)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	pthread_mutex_lock(&philo->data->print_mutix);
	if (philo->data->is_died != 1 && philo->data->full_data != 1)
		printf("%ld	%d	%s", current_time() - philo->data->start_time,
			philo->philo_id, string);
	pthread_mutex_unlock(&philo->data->print_mutix);
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
	if (philo->n_meal == philo->data->number_limit_meals)
		philo->nbr_meals_eat = philo->data->number_limit_meals;
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

void	ft_think(t_philo *philo)
{
	ft_printf(philo, "is thinking\n");
}

void	ft_usleep(int time, t_data *data)
{
	size_t	start_time;

	start_time = current_time();
	while (current_time() - start_time < (size_t)time)
	{
		if (get_var(&data->data_mutex, &data->is_died)
			|| get_var(&data->data_mutex, &data->full_data))
			return ;
		usleep(100);
	}
}

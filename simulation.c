/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:28:33 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/27 19:12:10 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_printf(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = current_time();
	philo->n_meal++;
	
	if (philo->n_meal == philo->data->number_limit_meals)
		philo->nbr_meals_eat = philo->data->number_limit_meals;
	pthread_mutex_unlock(&philo->data->data_mutex);
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

int simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = current_time();
	while (i < data->philo_n)
	{
		data->philo[i].last_meal = current_time();
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

// void	monitor(t_data *data)
// {
// 	int	i;
	
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < data->philo_n)
// 		{
// 			// usleep(200)
// 			if (is_philo_died(&data->philo[i]))
// 			{
// 				// printf("hhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\n");
// 				set_var(&data->data_mutex, &data->is_died, 1);
// 				pthread_mutex_lock(&data->print_mutix);
// 				if (get_var(&data->data_mutex, &data->is_died))
// 					printf("%ld	%d	died\n", current_time()
// 						- data->start_time, data->philo[i].philo_id);
// 				pthread_mutex_unlock(&data->print_mutix);
// 				return ;
// 			}
// 		}
// 		if (get_var(&data->data_mutex, &data->is_died))
// 			break ;
// 		if (philo_full(data))
// 			break ;
// 	}
// }


void	monitor(t_data *data)
{
	int	i;
	
	i = 0;
	while (1)
	{
		if (is_philo_died(&data->philo[i]))
		{
			set_var(&data->data_mutex, &data->is_died, 1);
			pthread_mutex_lock(&data->print_mutix);
			if (get_var(&data->data_mutex, &data->is_died))
				printf("%ld	%d	died\n", current_time()
					- data->start_time, data->philo[i].philo_id);
			pthread_mutex_unlock(&data->print_mutix);
			return ;
		}
		i++;
		if (i == data->philo_n)
			i = 0;
		if (get_var(&data->data_mutex, &data->is_died))
			break ;
		if (philo_full(data))
			break ;
	}
}

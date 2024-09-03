/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:38 by hben-laz          #+#    #+#             */
/*   Updated: 2024/09/01 12:07:21 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	data->is_full = 0;
	data->is_died = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philo)
		return (ft_error(2), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (ft_error(2), destroy_simulation(data, 0), 1);
	if (pthread_mutex_init(&data->print_mutix, NULL) != 0)
		return (ft_error(3), destroy_simulation(data, 0), 1);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (ft_error(3), destroy_simulation(data, 1), 1);
	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error(3), destroy_simulation(data, 1), 1);
		i++;
	}
	return (0);
}

void	initialize_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].n_meal = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philo_n;
		i++;
	}
}

int	ft_ptread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_join(data->philo[i].philo_th, NULL))
			return (ft_error(4), destroy_simulation(data, 1), 1);
		i++;
	}
	return (0);
}

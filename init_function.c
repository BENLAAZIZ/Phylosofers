/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:53:39 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/27 14:46:44 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->full_data = 0;
	data->is_died = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philo)
		return (write(2, "Malloc error\n", 13), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (write(2, "Malloc error\n", 13), 1);
	if (pthread_mutex_init(&data->print_mutix, NULL))
		return (write(2, "Mutex error\n", 12), 1);
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (write(2, "Mutex error\n", 12), 1);
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write(2, "Mutex error\n", 12), 1);
		i++;
	} 
	return (0);
}

void	initializ_philo(t_data *data)
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

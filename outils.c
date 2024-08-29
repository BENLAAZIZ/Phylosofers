/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:13:04 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/29 12:45:20 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (ft_error(5), 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	get_var(pthread_mutex_t *mutex, int *var)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	is_philo_dead(t_philo *philo)
{
	if (current_time() - (size_t)philo->last_meal
		>= (size_t)philo->data->time_to_die)
		return (1);
	return (0);
}

int	philo_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->number_limit_meals == -1)
		return (0);
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->philo[i].n_meal < data->number_limit_meals)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	pthread_mutex_lock(&data->data_mutex);
	data->full_data = 1;
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}

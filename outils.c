/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:13:04 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/28 16:12:35 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22), 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
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

int	get_var(pthread_mutex_t *mutex, int *var)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	set_var(pthread_mutex_t *mutex, int *var, int value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
	return (0);
}

int	is_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (current_time() - (size_t)philo->last_meal
		>= (size_t)philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
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
		if (data->philo[i].nbr_meals_eat < data->number_limit_meals)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	set_var(&data->data_mutex, &data->full_data, 1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:34:50 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/29 12:41:58 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int flag)
{
	write(2, "Error : ", 8);
	if (flag == 1)
		write(2, "Invalid argument\n", 17);
	if (flag == 2)
		write(2, "Malloc fail\n", 12);
	if (flag == 3)
		write(2, "Mutex fail\n", 11);
	if (flag == 4)
		write(2, "Thread fail\n", 12);
	if (flag == 5)
		write(2, "gettimeofday() fail\n", 22);
}

int	destroy_simulation(t_data *data, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		if (pthread_mutex_destroy(&data->print_mutix))
			return (1);
		if (pthread_mutex_destroy(&data->data_mutex))
			return (1);
		while (++i < data->philo_n)
		{
			if (pthread_mutex_destroy(&data->forks[i]))
				return (1);
		}
	}
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:50:17 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/26 11:50:42 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_mutix);
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

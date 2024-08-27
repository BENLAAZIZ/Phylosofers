/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:33:54 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/27 14:41:28 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->philo_id % 2 == 0)
		ft_usleep(60, philo->data);
	while (1)
	{
		if (get_var(&philo->data->data_mutex, &philo->data->is_died)
			|| get_var(&philo->data->data_mutex, &philo->data->full_data))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}


void	*one_thread(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	ft_printf(philo, "has taken a fork\n");
	ft_usleep(philo->data->time_to_die, philo->data);
	ft_printf(philo, "died\n");
	
	return (NULL);
}


void	ft_printf(t_philo *philo, char *string)
{
	long	start_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	start_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_lock(&philo->data->print_mutix);
	if (!get_var(&philo->data->data_mutex, &philo->data->is_died)
		&& !get_var(&philo->data->data_mutex, &philo->data->full_data))
		printf("%ld	%d	%s", current_time() - start_time, philo->philo_id, string);
	pthread_mutex_unlock(&philo->data->print_mutix);
}
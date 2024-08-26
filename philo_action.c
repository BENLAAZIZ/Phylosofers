/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:33:54 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/26 16:11:31 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->philo_id % 2 == 0)
		ft_usleep(60, philo->data);
	while (!get_var(&philo->data->data_mutex, &philo->data->is_died)
		&& !get_var(&philo->data->data_mutex, &philo->data->full_data))
	{
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
	ft_usleep(60, philo->data);
	ft_eat(philo);
	ft_sleep(philo);
	ft_think(philo);
	return (NULL);
}


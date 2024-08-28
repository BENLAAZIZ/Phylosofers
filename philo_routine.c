/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:20:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/28 15:23:34 by hben-laz         ###   ########.fr       */
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
		if (philo->nbr_meals_eat == philo->data->number_limit_meals)
			break ;
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
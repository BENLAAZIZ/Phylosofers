/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/09/03 17:06:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].last_meal = current_time();
		if (pthread_create(&data->philo[i].philo_th,
				NULL, &routine, &data->philo[i]) != 0)
			return (ft_error(4), 1);
		i++;
	}
	return (0);
}

int	creat_philo(t_data *data)
{
	initialize_philo(data);
	data->start_time = current_time();
	if (data->philo_n == 1)
	{
		if (pthread_create(&data->philo[0].philo_th, NULL,
				&one_philo, &data->philo[0]) != 0)
			return (ft_error(4), destroy_simulation(data, 1), 1);
		if (pthread_join(data->philo[0].philo_th, NULL) != 0)
			return (ft_error(4), destroy_simulation(data, 1), 1);
		return (destroy_simulation(data, 1), 1);
	}
	if (simulation(data) == 1)
		return (destroy_simulation(data, 1), 1);
	monitor(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ft_error(1), 1);
	if (check_pars(&data, argv) == 1)
		return (1);
	if (data.number_limit_meals == 0)
		return (0);
	if (ft_init_mutex(&data) == 1)
		return (1);
	if (creat_philo(&data) == 1)
		return (0);
	if (ft_ptread_join(&data) == 1)
		return (1);
	if (destroy_simulation(&data, 1))
		return (1);
	return (0);
}

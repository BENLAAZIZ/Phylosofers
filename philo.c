/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/28 15:31:36 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = current_time();
	while (i < data->philo_n)
	{
		data->philo[i].last_meal = current_time();
		if (pthread_create(&data->philo[i].philo_th, NULL, &routine, &data->philo[i]))
			return (write(2, "Thread error\n", 13), 1);
		i++;
	}
	return (0);
}

int	creat_philo(t_data *data)
{
	initializ_philo(data);
	if (data->philo_n == 1)
	{
		data->start_time = current_time();
		if (pthread_create(&data->philo[0].philo_th, NULL, &one_thread, &data->philo[0]))
			return (write(2, "Thread error\n", 13), 1);
		if (pthread_join(data->philo[0].philo_th, NULL))
			return(1);
		return (destroy_simulation(data), 1);
	}
	if (simulation(data) == 1)
		return (1);
	monitor(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid argument\n", 17), 1);
	if (check_pars(&data, argv) == 1)
		return (1);
	if (data.number_limit_meals == 0)
		return (0);
	if (ft_init_mutex(&data) == 1)
		return (1);
	if (creat_philo(&data) == 1)
		return (0);
	int	i = 0;
	while (i < data.philo_n)
	{
		if (pthread_join(data.philo[i].philo_th, NULL))
			return (write(2, "Thread error\n", 13), 1);
		i++;
	}
	if (destroy_simulation(&data))
		return (1);
	return (0);
}

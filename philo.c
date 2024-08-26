/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/26 17:03:26 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_philo(t_data *data)
{
	initializ_philo(data);
	if (data->philo_n == 1)
	{
		if (pthread_create(&data->philo[0].philo_th, NULL, &one_thread, &data->philo[0]))
			return (write(2, "Thread error\n", 13), 1);
		return (end_simulation(data), 1);
	}
	if (start_sim_simulation(data) == 1)
		return (1);
	monitor(data);
	return (0);
}

int	is_philo_died(t_philo *philo)
{
	if (current_time() - (size_t)philo->last_meal > (size_t)philo->data->time_to_die)
		return (1);
	return (0);
}

int	philo_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (data->philo[i].nbr_meals_eat < data->number_limit_meals)
			return (0);
		i++;
	}
	return (1);
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
		return (1);
	int	i = 0;
	while (i < data.philo_n)
	{
		if (pthread_join(data.philo[i].philo_th, NULL))
			return (write(2, "Thread error\n", 13), 1);
		i++;
	}
	if (end_simulation(&data))
		return (1);
	return (0);
}

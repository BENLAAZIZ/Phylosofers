/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:58:32 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/27 12:07:28 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sin(const char *str, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			return (-1);
		if (str[*i] == '+')
			(*i)++;
	}
	return (0);
}

int ft_isdigit(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (-1);
		if (str[i] == '\0')
			break ;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		f;
	char	*array;

	i = 0;
	f = 0;
	array = ft_strtrim(str, " ");
	if (!array)
		return (-1);
	if (check_sin(array, &i) == -1)
		return (free(array), -1);
	if (ft_isdigit(array + i) == -1)
		return (free(array), -1);
	while (array[i] >= '0' && array[i] <= '9')
	{	
		f = (f * 10) + array[i] - '0';
		if (f > 2147483647)
			return (free(array), -1);
		i++;
	}
	return (free(array), f);
}

int	check_pars(t_data *data, char **argv)
{
	data->philo_n = ft_atoi(argv[1]);
	if (data->philo_n <= 0)
		return (write(2, "Invalid argument\n", 17), 1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die <= 0)
		return (write(2, "Invalid argument\n", 17), 1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat <= 0)
		return (write(2, "Invalid argument\n", 17), 1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep <= 0)
		return (write(2, "Invalid argument\n", 17), 1);
	if (argv[5])
	{
		data->number_limit_meals = ft_atoi(argv[5]);
		if (data->number_limit_meals < 0)
			return (write(2, " Invalid number of meals\n", 25), 1);
	}
	else
		data->number_limit_meals = -1;
	return (0);
}

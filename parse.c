/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:58:32 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/19 20:50:07 by hben-laz         ###   ########.fr       */
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
		if ((str[i] >= 0 && str[i] <= 9))
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
	char	**array;

	i = 0;
	f = 0;
	array = ft_splith(str, ' ');
	if (!array)
		return (-1);
	if (array[1])
		return(free_split(array), -1);
	if (check_sin(array[0], &i) == -1)
		return (-1);
	if (ft_isdigit(array[0] + i) == -1)
		return (free_split(array), -1);
	while (array[0][i] >= '0' && array[0][i] <= '9')
	{	
		f = (f * 10) + array[0][i] - '0';
		if (f > 2147483647)
			return (-1);
		i++;
	}
	return (free_split(array), f);
}

void	check_pars(t_table *tab, char **argv)
{
	tab->philo_n = ft_atoi(argv[1]);
	printf("{%d}\n", tab->philo_n);
	if (tab->philo_n <= 0)
		printf("error pars n_philo \n");
	tab->time_to_die = ft_atoi(argv[2]) * 1000;
	if (tab->time_to_die <= 0 || (tab->time_to_die < 6000))
		printf("error pars time_to_die\n");
	tab->time_to_eat = ft_atoi(argv[3]) * 1000;
	if (tab->time_to_eat <= 0 || (tab->time_to_eat < 6000))
		printf("error pars time_to_eat\n");
	tab->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (tab->time_to_sleep <= 0 || (tab->time_to_sleep < 6000))
		printf("error pars time_to_sleep\n");
	if (argv[5])
		tab->number_limit_meals = ft_atoi(argv[5]);
	else
		tab->number_limit_meals = -1;
}
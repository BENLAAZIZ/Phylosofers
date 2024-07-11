/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/12 00:49:08 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

void	check_sin(const char *str, int *i, int *s)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*s *= -1;
		(*i)++;
	}
}

long	ft_atoi(const char *str)
{
	int				i;
	unsigned long	f;
	int				s;

	i = 0;
	f = 0;
	s = 1;

	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	check_sin(str, &i, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{	
		f = (f * 10) + str[i] - '0';
		if (f >= 9223372036854775807 && s == 1)
			return (-1);
		if (f > 9223372036854775808UL && s == -1)
			return (-1);
		i++;
	}
	if (f > 2147483647)
		return (-1);
	return ((long)f * s);
}

void	check_pars(t_table *tab, char **argv)
{
	tab->philo_n = ft_atoi(argv[1]);
	if (tab->philo_n <= 0)
		printf("error pars n_philo\n");
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

int main(int argc, char **argv)
{
	t_table	tab;
	(void)(argc);
	check_pars(&tab, argv);
}
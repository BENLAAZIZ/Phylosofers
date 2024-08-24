/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:55:29 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/24 18:45:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void v()
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_table	tab;
	// atexit(v);
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid argument\n", 17), 1);
	if (check_pars(&tab, argv) == 1)
		return (1);
	if (tab.number_limit_meals == 0)
		return (0);
	return (0);
}

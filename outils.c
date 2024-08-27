/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msassi <msassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:13:04 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/27 15:52:44 by msassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time()
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22), 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int get_var(pthread_mutex_t *mutex, int *var)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int set_var(pthread_mutex_t *mutex, int *var, int value)
{
	pthread_mutex_lock(mutex);
	// printf("hhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\nhhadadadaddad\n");	
	*var = value;
	pthread_mutex_unlock(mutex);
	return (0);
}


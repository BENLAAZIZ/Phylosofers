/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:16:47 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/26 15:33:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (*s != '\0')
	{
		l++;
		s++;
	}
	return (l);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;
	size_t	j;

	i = ft_strlen(s1);
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start_sim, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	size_t	i;
	char	*substr;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start_sim >= s_len)
		return (ft_strdup(""));
	substr_len = len;
	if (start_sim + substr_len > s_len) 
		substr_len = s_len - start_sim;
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (i < substr_len) 
	{
		substr[i] = s[start_sim + i];
		i++;
	}
	substr[substr_len] = '\0';
	return (substr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;
	size_t	j;

	if (s1 == NULL) 
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	i = 0;
	while (s1[i] &&  (s1[i] == ' '))
		i++;
	if (i == len_s1)
		return (ft_strdup(""));
	while (len_s1 > 0 && (s1[len_s1 - 1] == ' '))
		len_s1--;
	j = len_s1 - i;
	return (ft_substr(s1, i, j));
}

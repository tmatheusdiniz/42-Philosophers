/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:06:06 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/23 17:37:35 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i ++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = -sign;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	return (res * sign);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i ++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count ++;
		s ++;
	}
	return (count);
}

void	check_if_all_have_eaten(t_table *table, t_philo *philo)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (table->must_eat_count == -1)
		return ;
	pthread_mutex_lock(&table->meal_check_mutex);
	while ((size_t)i < philo->table->philos_num)
	{
		if (table->philos[i].meals_eaten < philo->table->must_eat_count)
		{
			flag = 0;
			break ;
		}
		i ++;
	}
	pthread_mutex_unlock(&table->meal_check_mutex);
	if (flag)
	{
		pthread_mutex_lock(&table->stop_mutex);
		table->simulation_stop = 1;
		pthread_mutex_unlock(&table->stop_mutex);
	}
}

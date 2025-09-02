/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:34:03 by mreinald          #+#    #+#             */
/*   Updated: 2025/09/01 18:52:24 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&table->forks[i]);
}

void	clean_all(t_table *table)
{
	if (table->philos)
	{
		free (table->philos);
		table->philos = NULL;
	}
	if (table->forks)
	{
		destroy_forks(table, table->philos_num);
		free (table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_check_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
}

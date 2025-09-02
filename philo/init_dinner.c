/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:48:51 by mreinald          #+#    #+#             */
/*   Updated: 2025/09/01 23:45:05 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	handle_one_thread(t_table *table);

static int	check_should_finish(t_table *table)
{
	int	should_stop;

	pthread_mutex_lock(&table->stop_mutex);
	should_stop = table->simulation_stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (should_stop);
}

void	*monitor_routine(void *arg)
{
	t_table		*table;
	int			i;
	long long	time_meal;

	table = (t_table *)arg;
	while (!check_should_finish(table))
	{
		i = 0;
		while (i < (int)table->philos_num)
		{
			pthread_mutex_lock(&table->meal_check_mutex);
			time_meal = get_current_time() - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->meal_check_mutex);
			if (time_meal > (long long)table->time_die)
			{
				print_state(&table->philos[i], DIED);
				pthread_mutex_lock(&table->stop_mutex);
				table->simulation_stop = 1;
				return (pthread_mutex_unlock(&table->stop_mutex), NULL);
			}
			i ++;
		}
		check_if_all_have_eaten(table, table->philos);
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_should_finish(philo->table))
	{
		eating(philo);
		thinking_sleeping(philo);
		usleep(200);
	}
	return (NULL);
}

static void	handle_one_thread(t_table *table)
{
	long long	death_time;

	table->start_time = get_current_time();
	table->philos[0].last_meal_time = table->start_time;
	print_state(&table->philos[0], FORK_TAKEN);
	precise_sleep(table->time_die);
	death_time = get_current_time() - table->start_time;
	printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET,
		death_time, table->philos[0].id, "died", "💀");
}

int	init_threads(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (table->philos_num == 1)
		return (handle_one_thread(table), 1);
	while ((size_t)i < table->philos_num)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&routine, (void *)&table->philos[i]))
			return (error_msg("Failed to create thread"), 1);
		i ++;
	}
	pthread_create(&monitor, NULL, &monitor_routine, (void *)table);
	i = 0;
	while ((size_t)i < table->philos_num)
	{
		if (pthread_join(table->philos[i++].thread, NULL))
			return (error_msg("Failed to join thread"), 1);
	}
	pthread_join(monitor, NULL);
	return (0);
}

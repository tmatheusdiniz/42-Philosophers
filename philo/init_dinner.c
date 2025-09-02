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
#include <pthread.h>

static int	check_philosopher_death(t_table *table, int i);

static void	aux_check_philosopher_d(t_table *table, int i,
		long long *time_since_meal, long long *time_when_should_die)
{
	long long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&table->check_last_meal);
	*time_since_meal = current_time - table->philos[i].last_meal_time;
	*time_when_should_die = table->philos[i].last_meal_time + table->time_die;
	pthread_mutex_unlock(&table->check_last_meal);
}

static int	check_philosopher_death(t_table *table, int i)
{
	long long	death_time_from_start;
	long long	time_when_should_die;
	long long	time_since_meal;

	aux_check_philosopher_d(table, i, &time_since_meal, &time_when_should_die);
	if (time_since_meal >= (long long)table->time_die)
	{
		death_time_from_start = time_when_should_die - table->start_time;
		pthread_mutex_lock(&table->check_stop_s);
		if (!table->simulation_stop)
		{
			table->simulation_stop = 1;
			pthread_mutex_unlock(&table->check_stop_s);
			pthread_mutex_lock(&table->print_mutex);
			printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET,
				death_time_from_start, table->philos[i].id, "died", "💀");
			pthread_mutex_unlock(&table->print_mutex);
		}
		else
			pthread_mutex_unlock(&table->check_stop_s);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (1)
	{
		i = -1;
		while (++i < (int)table->philos_num)
		{
			if (check_philosopher_death(table, i))
				return (NULL);
		}
		check_if_all_have_eaten(table, table->philos);
		if (check_should_finish(table))
			return (NULL);
		usleep(500);
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
		if (check_should_finish(philo->table))
			break ;
		thinking_sleeping(philo);
		usleep(100);
	}
	return (NULL);
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

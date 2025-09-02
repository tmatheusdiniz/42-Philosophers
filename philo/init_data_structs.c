/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:01:04 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/24 00:26:02 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	init_table(t_table *table, char **str)
{
	table->philos_num = ft_atoi(str[1]);
	table->time_die = ft_atoi(str[2]);
	table->time_eat = ft_atoi(str[3]);
	table->time_sleep = ft_atoi(str[4]);
	if (str[5])
		table->must_eat_count = ft_atoi(str[5]);
	else
		table->must_eat_count = -1;
	table->start_time = get_current_time();
	table->simulation_stop = 0;
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->philos_num);
	if (!table->philos)
		return (error_msg("Memory allocation failed:"), 1);
	return (0);
}

static int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->check_last_meal, NULL))
		return (1);
	if (pthread_mutex_init(&table->check_stop_s, NULL))
		return (1);
	if (pthread_mutex_init(&table->check_all_eaten, NULL))
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_num);
	if (!table->forks)
		return (error_msg("Memory allocation failed:"), 1);
	i = 0;
	while (i < (int)table->philos_num)
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (1);
	return (0);
}

static void	init_philosophers(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->philos_num)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = table->start_time;
		philo[i].left_fork_id = i;
		philo[i].right_fork_id = (i + 1) % table->philos_num;
		philo[i].table = table;
		i++;
	}
}

int	start_structs(t_table *table, char **str)
{
	if (init_table(table, str))
		return (1);
	if (init_mutexes(table))
	{
		error_msg("Mutex initialization failed");
		return (1);
	}
	init_philosophers(table->philos, table);
	return (0);
}

void	handle_one_thread(t_table *table)
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

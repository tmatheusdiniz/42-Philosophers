/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:47:35 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/27 10:48:38 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>
#include <stddef.h>

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork_id]);
}

int	take_fork(t_philo *philo)
{
	int	first_f;
	int	second_f;

	first_f = philo->left_fork_id;
	second_f = philo->right_fork_id;
	pthread_mutex_lock(&philo->table->forks[first_f]);
	print_state(philo, FORK_TAKEN);
	if (philo->table->philos_num == 1)
		return (usleep(philo->table->time_die * 1000), 1);
	pthread_mutex_lock(&philo->table->forks[second_f]);
	print_state(philo, FORK_TAKEN);
	return (0);
}

int	thinking_sleeping(t_philo *philo)
{
	print_state(philo, SLEEPING);
	precise_sleep(philo->table->time_sleep);
	print_state(philo, THINKING);
	return (0);
}

int	eating(t_philo *philo)
{
	take_fork(philo);
	print_state(philo, EATING);
	pthread_mutex_lock(&philo->table->meal_check_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->meal_check_mutex);
	precise_sleep(philo->table->time_eat);
	++philo->meals_eaten;
	release_forks(philo);
	return (0);
}

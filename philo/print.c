/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:04:56 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/30 22:05:05 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error_msg(char *str)
{
	printf("%s Error: %s%s\n", RED, str, RESET);
	return (1);
}

void	print_state(t_philo *philo, t_state state)
{
	long long	time;

	if (!philo->table->simulation_stop)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		time = time_diff(philo->table->start_time, get_current_time());
		if (state == FORK_TAKEN)
			printf(WHITE "%4lld " RESET BOLD "%2i " GREEN "%16s %s\n" RESET,
				time, philo->id, "has taken a fork", "🍴");
		else if (state == EATING)
			printf(WHITE "%4lld " RESET BOLD "%2i " BLUE "%16s %s\n" RESET,
				time, philo->id, "is eating", "🍝");
		else if (state == SLEEPING)
			printf(WHITE "%4lld " RESET BOLD "%2i " CYAN "%16s %s\n" RESET,
				time, philo->id, "is sleeping", "😴");
		else if (state == THINKING)
			printf(WHITE "%4lld " RESET BOLD "%2i " MAGENTA "%16s %s\n" RESET,
				time, philo->id, "is thinking", "💭");
		else if (state == DIED)
			printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET, time,
				philo->id, "died", "💀");
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

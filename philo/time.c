/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:56:52 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/24 00:16:00 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	precise_sleep(unsigned long long time)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(50);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

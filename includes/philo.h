/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:18:37 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/16 00:42:50 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_philos
{
	int				id;
	size_t			philos_num;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			time_die;
	pthread_t		thread;
	struct s_table	*table;
}			t_philos;

typedef struct s_table
{
	pthread_t	table;
	
}				t_table;

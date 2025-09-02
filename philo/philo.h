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

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <colors.h>

# define MAX_PHILOS 200

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	FORK_TAKEN,
	DIED
}				t_state;

typedef struct s_table
{
	size_t			philos_num;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				must_eat_count;
	size_t			start_time;
	int				simulation_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_last_meal;
	pthread_mutex_t	check_stop_s;
	pthread_mutex_t	check_all_eaten;
	struct s_philo	*philos;
}				t_table;

typedef struct s_philo
{
	int				id;
	size_t			last_meal_time;
	int				meals_eaten;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread;
	t_table			*table;
}				t_philo;

// Main
int			main(int v, char **str);

// Thread
int			init_threads(t_table *table);
int			start_structs(t_table *table, char **str);
void		handle_one_thread(t_table *table);

// Tasks
int			eating(t_philo *philo);
int			thinking_sleeping(t_philo *philo);
int			take_fork(t_philo *philo);

// Time
size_t		get_current_time(void);
long long	time_diff(long long past, long long present);
void		precise_sleep(unsigned long long time);

// Print
int			error_msg(char *str);
void		print_state(t_philo *philo, t_state state);

// Clean
void		clean_all(t_table *table);
void		destroy_forks(t_table *table, int count);

// Utils
int			ft_atoi(const char *nptr);
int			ft_isnum(char *str);
size_t		ft_strlen(const char *s);
int			check_should_finish(t_table *table);
void		check_if_all_have_eaten(t_table *table, t_philo *philo);

#endif

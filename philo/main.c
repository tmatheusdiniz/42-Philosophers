/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 22:18:05 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/15 22:18:24 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_input(int v, char **str)
{
	if (v < 5 || v > 6)
		return (printf(RED "Usage:\n" BLUE
				"./philo 5 500 600 800 [optional]\n" RESET));
	if (ft_atoi(str[1]) <= 0 || ft_atoi(str[1]) > MAX_PHILOS)
		return (printf(RED "Invalid number of philosophers\n" RESET));
	if (ft_atoi(str[2]) <= 0 || ft_isnum(str[2]))
		return (printf(RED "Invalid time_to_die\n" RESET));
	if (ft_atoi(str[3]) <= 0 || ft_isnum(str[3]))
		return (printf(RED "Invalid time_to_eat\n" RESET));
	if (ft_atoi(str[4]) <= 0 || ft_isnum(str[4]))
		return (printf(RED "Invalid time_to_sleep\n" RESET));
	if (v == 6 && (ft_atoi(str[5]) <= 0 || ft_isnum(str[5])))
		return (printf(RED "Invalid eat_times\n" RESET));
	return (0);
}

int	main(int v, char **str)
{
	t_table	table;

	if (check_input(v, str))
		return (1);
	if (start_structs(&table, str))
	{
		clean_all(&table);
		return (1);
	}
	if (init_threads(&table))
	{
		clean_all(&table);
		return (1);
	}
	clean_all(&table);
}

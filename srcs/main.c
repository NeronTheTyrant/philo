/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 22:43:08 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/28 16:12:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc != 5 && argc != 6)
		return (0);
	ft_bzero(&table, sizeof(table));
	if (parse_args(&table, argc, argv) == 0)
		return (0);
	init_table(&table);
	init_philo(&table);
/*	while (1)
	{
		if (table.sig == SIG_TERM_DIE || table.sig == SIG_TERM_MEALS)
			break ;
		usleep(1000);
	}*/
	i = 0;
	while (i < table.philonum)
	{
		pthread_join(table.thread[i], NULL);
		i++;
	}
	philo_free(&table);
	exit(0);
}

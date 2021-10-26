/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 22:43:08 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/19 22:58:04 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	ft_bzero(&table, sizeof(table));
	if (parse_args(&table, argc, argv) == 0)
		return (0);
	init_table(&table);
	init_philo(&table);
	while (1)
	{
		if (table.sig == SIG_TERM_DIE || table.sig == SIG_TERM_MEALS)
			break ;
	}
	philo_free(&table);
	exit(0);
}

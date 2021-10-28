/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:50:21 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/28 16:12:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philonum);
	table->fork = malloc(sizeof(t_fork) * table->philonum);
	table->thread = malloc(sizeof(pthread_t) * table->philonum);
	if (table->philo == NULL || table->fork == NULL || table->thread == NULL)
		return (0);
	pthread_mutex_init(&table->msg, NULL);
	pthread_mutex_init(&table->sig_mtx, NULL);
	pthread_mutex_init(&table->meals, NULL);
	while (i < table->philonum)
	{
		pthread_mutex_init(&table->fork[i].mtx, NULL);
		table->fork[i].status = UNLOCKED;
		i++;
	}
	table->start_time = gettime();
	return (1);
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philonum)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = &table->fork[i];
		if (i + 1 == table->philonum)
			table->philo[i].right_fork = &table->fork[0];
		else
			table->philo[i].right_fork = &table->fork[i + 1];
		table->philo[i].mealnum = 0;
		table->philo[i].last_meal = gettime();
		pthread_create(&table->thread[i], NULL, &philo_life, &table->philo[i]);
		i++;
	}
}

void	philo_free(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philonum)
	{
		pthread_mutex_destroy(&table->fork[i].mtx);
		i++;
	}
	pthread_mutex_destroy(&table->msg);
	pthread_mutex_destroy(&table->sig_mtx);
	free(table->philo);
	free(table->thread);
	free(table->fork);
}

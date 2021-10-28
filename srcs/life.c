/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:32 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/28 17:56:34 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_usleep(t_table *table, unsigned long int t)
{
	unsigned long int	time;
	int					sig;

	time = gettime() + t;
	sig = 0;
	while (gettime() < time && sig != SIG_TERM_DIE && sig != SIG_TERM_MEALS)
	{
		pthread_mutex_lock(&table->sig_mtx);
		sig = table->sig;
		pthread_mutex_unlock(&table->sig_mtx);
		usleep(10);
	}
}

void	philo_think(t_philo *philo, t_table *table)
{
	philo_msg("is thinking", philo, table);
	if (table->time_to_die - (gettime() - philo->last_meal) <= 15)
		philo_usleep(table, 1);
	else
		philo_usleep(table, 10);
}

int	philo_eat(t_philo *philo, t_table *table)
{
	if (table->philonum == 1)
		philo_msg("has taken a fork", philo, table);
	if (get_forks(philo, table) == -1)
		return (-1);
	philo_msg("has taken a fork", philo, table);
	philo_msg("has taken a fork", philo, table);
	philo_msg("is eating", philo, table);
	philo->mealnum++;
	pthread_mutex_lock(&table->meals);
	if (philo->mealnum == table->mealcount)
		table->philo_mealcount++;
	if (table->philo_mealcount == table->philonum)
	{
		pthread_mutex_lock(&table->sig_mtx);
		table->sig = SIG_TERM_MEALS;
		pthread_mutex_unlock(&table->sig_mtx);
		pthread_mutex_unlock(&table->meals);
		return (-1);
	}
	pthread_mutex_unlock(&table->meals);
	philo->last_meal = gettime();
	philo_usleep(table, gettimetosleep(philo->last_meal, table->time_to_eat,
			table->time_to_die));
	drop_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo, t_table *table)
{
	philo_msg("is sleeping", philo, table);
	philo_usleep(table, gettimetosleep(philo->last_meal, table->time_to_sleep,
			table->time_to_die));
	return (0);
}

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
		if (check_term(philo, table) == 1)
			break ;
		philo_think(philo, table);
		if (philo_eat(philo, table) == -1)
			break ;
		if (check_term(philo, table) == 1)
			break ;
		philo_sleep(philo, table);
	}
	return (NULL);
}

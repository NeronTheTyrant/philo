/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 22:07:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/19 23:48:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# define SIG_TERM_DIE	1
# define SIG_TERM_MEALS	2

typedef enum e_forkstatus
{
	UNLOCKED = 0,
	LOCKED
}	t_forkstatus;

typedef struct s_fork
{
	t_forkstatus	status;
	pthread_mutex_t	mtx;
}	t_fork;

typedef struct s_philo
{
	int					id;
	t_fork				*right_fork;
	t_fork				*left_fork;
	int					mealnum;
	long				last_meal;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	long unsigned int	time_to_die;
	long unsigned int	time_to_eat;
	long unsigned int	time_to_sleep;
	int					mealcount;
	int					philo_mealcount;
	long unsigned int	start_time;
	int					sig;
	int					philonum;
	t_philo				*philo;
	pthread_t			*thread;
	t_fork				*fork;
	pthread_mutex_t		msg;
	pthread_mutex_t		sig_mtx;
	pthread_mutex_t		meals;
}	t_table;

/*
** Init & Free (init_free.c)
*/

int					init_table(t_table *table);
void				init_philo(t_table *table);
void				philo_free(t_table *table);

/*
** Parse (parse.c)
*/

int					parse_args(t_table *table, int argc, char **argv);

/*
** Forks (forks.c)
*/

int					get_forks(t_philo *philo, t_table *table);
int					grab_fork(t_fork *fork);
void				drop_forks(t_philo *philo);

/*
** Thread Routine (life.c)
*/

void				*philo_life(void *data);

/*
** Thread Termination (death.c)
*/

int					check_term(t_philo *philo, t_table *table);

/*
** Utils & Tools (utils.c)
*/

void				philo_msg(char *str, t_philo *philo, t_table *table);
unsigned long int	gettimetosleep(unsigned long int last_meal,
						unsigned long int time_to_do,
						unsigned long int time_to_die);
unsigned long int	gettime(void);

/*
** Utils from Libft (libft_utils.c)
*/

int					ft_strcheck_each(char *str, int (*f)(char c));
int					ft_isdigit(char c);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);

#endif

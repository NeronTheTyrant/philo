/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:44:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/18 16:15:42 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** usage: checks ever character of string *str using function (*f).
** return: returns 1 if every call to (*f) returns 1. Otherwise, returns 0
*/

int	ft_strcheck_each(char *str, int (*f)(char c))
{
	while (*str != '\0')
	{
		if ((*f)(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

/*
** return: 1 if "c" is num, 0 if not
*/

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

/*
** usage: sets NULL bytes in n bytes of s array. same as ft_memset(s, '\0').
** return: void
*/

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*m;

	i = 0;
	m = s;
	while (i < n)
	{
		m[i] = '\0';
		i++;
	}
}

/*
** return: length of string s
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** usage: converts start of string into int
** return: the conversion of string str into int. 0 if no number is found.
*/

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 18:43:35 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 03:29:22 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "Error: get_time()\n", 19);
		return (ULONG_MAX);
	}
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

/**
 * @brief	get the time difference in milliseconds
 * @brief	between the current time and the start time
 */
unsigned long	get_time_d(unsigned long start_time)
{
	unsigned long	current_time;

	current_time = get_time();
	if (current_time == ULONG_MAX)
		return (ULONG_MAX);
	return (current_time - start_time);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief	sleep for a given time in milliseconds
 */
void	ft_zzz(unsigned long time)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time_d(start_time) < time)
		usleep(500);
}

/**
 * @brief	sets last_ate to the start time
 *@brief	for each philosopher
*/
void	set_time_last_eat(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		p->m_data->philos[i].last_ate = p->start_time;
		i++;
	}
}

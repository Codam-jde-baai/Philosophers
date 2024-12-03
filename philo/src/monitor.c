/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 23:14:38 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 03:25:08 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_dead(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->p_data->m_data->writing);
	printf("%lu %d %s\n", get_time_d(philo->p_data->start_time), philo->id,
		message);
	pthread_mutex_unlock(&philo->p_data->m_data->writing);
}

bool	check_philo_dead(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_lock(&p->m_data->philos[i].meal_lock);
		if (!p->m_data->philos[i].eating)
		{
			if (get_time_d(p->m_data->philos[i].last_ate)
				> (unsigned long)p->time_to_die)
			{
				pthread_mutex_unlock(&p->m_data->philos[i].meal_lock);
				pthread_mutex_lock(&p->m_data->state_mutex);
				p->m_data->p_state = END;
				pthread_mutex_unlock(&p->m_data->state_mutex);
				print_dead(&p->m_data->philos[i], DIED_MSG);
				return (true);
			}
		}
		pthread_mutex_unlock(&p->m_data->philos[i].meal_lock);
		i++;
	}
	return (false);
}

bool	check_philo_finished(t_program *p)
{
	int	i;
	int	n_finished;

	i = 0;
	n_finished = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_lock(&p->m_data->philos[i].meal_lock);
		if (p->m_data->philos[i].meal_count >= p->must_eat)
			n_finished++;
		pthread_mutex_unlock(&p->m_data->philos[i].meal_lock);
		i++;
	}
	if (n_finished == p->n_philo)
	{
		pthread_mutex_lock(&p->m_data->state_mutex);
		p->m_data->p_state = END;
		pthread_mutex_unlock(&p->m_data->state_mutex);
		return (true);
	}
	return (false);
}

/**
 * @brief monitors the philosophers
 * @brief checks if a philosopher has died
 * @brief checks if a philosopher has eaten max times
*/
void	start_monitor(t_program *p)
{
	if (p->must_eat == -1)
	{
		while (1)
		{
			if (check_philo_dead(p))
				return ;
		}
	}
	while (1)
	{
		if (check_philo_dead(p))
			return ;
		if (check_philo_finished(p))
			return ;
	}
}

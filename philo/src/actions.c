/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:46:41 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 14:11:47 by jde-baai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief prints time, philosopher id and message
 * @return true if the philosopher is still alive, false if not
 */
bool	print_message(t_philo *philo, char *message)
{
	if (!continue_routine(philo))
		return (false);
	pthread_mutex_lock(&philo->p_data->m_data->writing);
	printf("%lu %d %s\n", get_time_d(philo->p_data->start_time), philo->id,
		message);
	pthread_mutex_unlock(&philo->p_data->m_data->writing);
	return (true);
}

static void	unlock(t_philo *philo, bool fork_left, bool fork_right)
{
	if (fork_left)
		pthread_mutex_unlock(&philo->fork_left);
	if (fork_right)
		pthread_mutex_unlock(philo->fork_right);
}

/**
 * @brief philosopher eat action
 */
bool	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left);
	if (!print_message(philo, FORK_MSG))
		return (unlock(philo, true, false), false);
	pthread_mutex_lock(philo->fork_right);
	if (!print_message(philo, FORK_MSG))
		return (unlock(philo, true, true), false);
	if (!print_message(philo, EAT_MSG))
		return (unlock(philo, true, true), false);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = true;
	philo->last_ate = get_time();
	if (philo->p_data->must_eat != -1)
	{
		philo->meal_count++;
	}
	pthread_mutex_unlock(&philo->meal_lock);
	ft_zzz(philo->p_data->time_to_eat);
	unlock(philo, true, true);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal_lock);
	return (true);
}

/**
 * @brief philosopher sleep action
 */
bool	philo_sleep(t_philo *philo)
{
	if (!print_message(philo, SLEEP_MSG))
		return (false);
	ft_zzz(philo->p_data->time_to_sleep);
	return (true);
}

/**
 * @brief philosopher think action
 */
bool	philo_think(t_philo *philo)
{
	if (!print_message(philo, THINK_MSG))
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 17:27:05 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 13:28:21 by jde-baai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

/**
 * @brief	validate the input arguments
 */
bool	validate_args(char **argv)
{
	size_t	str;
	size_t	i;

	str = 1;
	while (argv[str])
	{
		i = 0;
		while (argv[str][i])
		{
			if (!ft_isdigit(argv[str][i]))
			{
				write(1, "Error: ", 8);
				write(1, argv[str], ft_strlen(argv[str]));
				write(1, ": is not a positive numerical input\n", 37);
				return (false);
			}
			i++;
		}
		str++;
	}
	return (true);
}

static int	philo_atoi(char *str)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (str[i])
	{
		if (out == INT_MAX)
			return (-1);
		out = out * 10 + (str[i] - '0');
		i++;
	}
	return (out);
}

/**
 * @brief	checks if the input arguments are valid
 * @brief 	if valid stores in t_program
 */
bool	input_check(t_program *p, int argc, char **argv)
{
	p->n_philo = philo_atoi(argv[1]);
	if (p->n_philo <= 0)
		return (write(1, "Error: 1st arg:", 16), false);
	p->time_to_die = philo_atoi(argv[2]);
	if (p->time_to_die <= 0)
		return (write(1, "Error: 2nd arg:", 16), false);
	p->time_to_eat = philo_atoi(argv[3]);
	if (p->time_to_eat <= 0)
		return (write(1, "Error: 3rd arg:", 16), false);
	p->time_to_sleep = philo_atoi(argv[4]);
	if (p->time_to_sleep <= 0)
		return (write(1, "Error: 4th arg:", 16), false);
	if (argc == 5)
		p->must_eat = -1;
	else
	{
		p->must_eat = philo_atoi(argv[5]);
		if (p->must_eat <= 0)
			return (write(1, "Error: 5th arg:", 16), false);
	}
	return (true);
}

/**
 * @brief	inits the t_program and t_monitor structs
 * @brief	parses the input arguments
 */
t_program	*parse_args(int argc, char **argv)
{
	t_program	*p;
	int			status;

	p = malloc(sizeof(t_program));
	if (!p)
		return (write(1, "Error: Malloc\n", 15), NULL);
	if (!input_check(p, argc, argv))
	{
		write(1, "input needs to be greater than 0 and smaller than MAX_INT\n",
			59);
		return (free(p), NULL);
	}
	status = init_monitor(p);
	if (status < 0)
	{
		free(p);
		if (status == -1)
			return (write(1, "Error: Malloc\n", 15), NULL);
		if (status == -2)
			return (write(1, "Error: Mutex\n", 14), NULL);
	}
	return (p);
}

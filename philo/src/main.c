/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 17:09:29 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/10/06 23:37:13 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	clean_up(t_program *program)
{
	clean_monitor(program);
	free(program);
}

static int	arg_error(void)
{
	write(1, "Error: incorrect amount of arguments\n", 38);
	write(1, "Please input:\n", 15);
	write(1, "1. number_of_philosophers\n", 27);
	write(1, "2. time_to_die\n", 16);
	write(1, "3. time_to_eat\n", 16);
	write(1, "4. time_to_sleep\n", 18);
	write(1, "5. (OPTIONAL) number_of_times_each_philosopher_must_eat\n", 57);
	return (1);
}

int	run_program(t_program *program)
{
	int	thread_count;

	thread_count = 0;
	program->start_time = get_time();
	if (program->start_time == ULONG_MAX)
		return (write(1, "Error: get time\n", 17), false);
	set_time_last_eat(program);
	if (!create_threads(program, &thread_count))
	{
		if (thread_count == 0)
			return (clean_up(program), 1);
		pthread_mutex_lock(&program->m_data->state_mutex);
		program->m_data->p_state = END;
		pthread_mutex_unlock(&program->m_data->state_mutex);
		join_threads(program, thread_count);
		clean_up(program);
		write(1, "Error: pthread_create\n", 22);
		return (1);
	}
	start_monitor(program);
	if (!join_threads(program, thread_count))
		return (clean_up(program), 1);
	clean_up(program);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 5 && argc != 6)
		return (arg_error());
	if (!validate_args(argv))
		return (1);
	program = parse_args(argc, argv);
	if (!program)
		return (1);
	return (run_program(program));
}

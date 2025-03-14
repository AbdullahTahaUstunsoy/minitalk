/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:43:55 by austunso          #+#    #+#             */
/*   Updated: 2025/03/14 21:28:33 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_process_id(int number)
{
	char	character;

	if (number >= 10)
	{
		print_process_id(number / 10);
	}
	character = '0' + (number % 10);
	write(1, &character, 1);
}

static void	signal_handler(int signal, siginfo_t *info, void *contxt)
{
	static int	bit_position;
	static char	character;
	int			shifted_bit;

	(void)contxt;
	shifted_bit = 0;
	if (signal == SIGUSR1)
	{
		shifted_bit = 1 << bit_position;
		character = character | shifted_bit;
	}
	bit_position++;
	if (bit_position == 8)
	{
		write(1, &character, 1);
		bit_position = 0;
		character = 0;
	}
	kill (info->si_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;

	(void)argv;
	if (argc != 1)
	{
		write(2, "Too many arguments\n", 19);
		return (0);
	}
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	server_pid = getpid();
	write(1, "Server PID : ", 13);
	print_process_id(server_pid);
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: Could not set up signal handlers\n", 40);
		return (0);
	}
	while (1)
		pause();
}

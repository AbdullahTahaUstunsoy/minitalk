/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:29:31 by austunso          #+#    #+#             */
/*   Updated: 2025/03/14 21:21:26 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_confirm_flag;

static int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while ((str[i] >= 48 && str[i] <= 57))
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

static void	ft_signal_confirm(int signal)
{
	if (signal == SIGUSR1)
	{
		g_confirm_flag = 1;
		write(1, "signal received\n", 16);
	}
}

static void	detect_bits(int server_pid, char character)
{
	int	bit_position;

	bit_position = 0;
	while (bit_position < 8)
	{
		g_confirm_flag = 0;
		if (((character >> bit_position) & 1) == 1)
			kill(server_pid, SIGUSR1);
		else if (((character >> bit_position) & 1) == 0)
			kill(server_pid, SIGUSR2);
		bit_position++;
		if (g_confirm_flag == 0)
			pause();
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	index;

	if (argc != 3)
	{
		write (2, "Usage: ./client <PID> <Message>\n", 33);
		return (0);
	}
	signal(SIGUSR1, ft_signal_confirm);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
	{
		write(2, "Invalid process id", 18);
		return (0);
	}
	index = 0;
	while (argv[2][index] != '\0')
	{
		detect_bits(server_pid, argv[2][index]);
		index++;
	}
	return (0);
}

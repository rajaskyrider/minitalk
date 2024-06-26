/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:52:39 by rpandipe          #+#    #+#             */
/*   Updated: 2024/04/22 11:46:23 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_status;

static void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	write(1, &c, 1);
}

static int	ft_atoi(const char *nptr)
{
	int	ans;
	int	sign;
	int	i;

	ans = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ans = ans * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * ans);
}

void	sig_handler(int sign, siginfo_t *info, void *context)
{
	static int	i;

	(void)info;
	(void)context;
	g_status = 1;
	if (sign == SIGUSR2)
		i++;
	else if (sign == SIGUSR1)
	{
		write(1, "Number of bytes recieved is ", 28);
		ft_putnbr(i / 8);
		write(1, "\n", 1);
	}
}

void	ft_ctob(int pid, char c)
{
	int		i;
	int		timer;

	i = 0;
	while (i < 8)
	{
		timer = 1;
		g_status = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_status != 1 && timer++)
		{
			if (timer == 50)
			{
				write (1, "Server Issues\n", 15);
				exit (1);
			}
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sa;

	i = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (argc == 3 && (sigaction(SIGUSR1, &sa, NULL) != -1 && \
		sigaction(SIGUSR2, &sa, NULL) != -1))
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != 0)
		{
			ft_ctob(pid, argv[2][i]);
			i++;
		}
		ft_ctob(pid, '\0');
	}
	else
	{
		write (1, "Error\n", 6);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:49:53 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/24 13:19:02 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int	count_hex(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

int	r_puthex(unsigned int n)
{
	unsigned int l;

	l = n;
	if (l >= 16)
	{
		r_puthex(l / 16);
		r_puthex(l % 16);
	}
	else
	{
		if (l < 10)
			l += 48;
		else
			l += 'a' - 10;
		write(1, &l, 1);
	}
	return(count_hex(n));
}

int	count_int(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	r_putnbr(int n)
{
	int  l;

	l = n;
	if (l == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (l < 0)
	{
		write(1, "-", 1);
		l = -l;
	}
	if (l >= 10)
	{
		r_putnbr(l / 10);
		r_putnbr(l % 10);
	}
	else
	{
		l += 48;
		write(1, &l, 1);
	}
	return (count_int(n));
}

int r_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while(s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	handle_arg(char c, va_list args)
{
	if (c == 'd')
		return(r_putnbr(va_arg(args, int)));	
	if (c == 'x')
		return(r_puthex(va_arg(args, unsigned int)));
	if (c == 's')
		return (r_putstr(va_arg(args, char *)));
	if (c == '%')
		{
			write(1, "%", 1);
			return (1);
		}
	return (0);
}

int	ft_printf(char	*format, ...)
{
	va_list args;
	int	i;
	int	count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += handle_arg(format[i + 1], args);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

/*int	main (void)
{
	int	i = 0;
	int	j = 0;

	i = printf("hello %s, %d, %x\n", "world", -0, 2147483648);
	j = ft_printf("hello %s, %d, %x\n", "world", -0, 2147483648);
	printf("og: %d, mine: %d", i, j);
}*/

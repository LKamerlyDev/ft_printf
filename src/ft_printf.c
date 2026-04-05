/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:25 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 17:20:54 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	ssize_t	count;
	va_list	args;
	t_flag	flags;

	va_start(args, format);
	count = 0;
	while (*format != '\0')
	{
		ft_memset(&flags, 0, sizeof(t_flag));
		if (*format == '%')
			count += ft_args_process(&format, &flags, args);
		else
			count += ft_write(1, format, 1, &flags);
		if (flags.errno > 0)
		{
			count = -(flags.errno);
			break ;
		}
		format++;
	}
	va_end(args);
	return (count);
}

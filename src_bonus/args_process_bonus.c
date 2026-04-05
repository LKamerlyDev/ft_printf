/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:11:02 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 13:28:58 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_process_type(char c, ssize_t *count, t_flag *flags, va_list args)
{
	if (c == 'c')
		*count += ft_print_char(flags, va_arg(args, int));
	else if (c == 's')
		*count += ft_print_str(flags, va_arg(args, char *));
	else if (c == 'd')
		*count += ft_print_digits(flags, va_arg(args, int), c);
	else if (c == 'x')
		*count += ft_print_hexa_digits_lower(flags, va_arg(args, int));
	else if (c == 'X')
		*count += ft_print_hexa_digits_upper(flags, va_arg(args, int));
	else if (c == 'p')
		*count += ft_print_ptr(flags, va_arg(args, void *));
	else if (c == 'i')
		*count += ft_print_digits(flags, va_arg(args, int), c);
	else if (c == 'u')
		*count += ft_print_digits(flags, (unsigned long)va_arg(args,
					unsigned int), c);
	else if (c == '%')
		*count += (ft_write(1, "%", 1, flags));
}

ssize_t	ft_args_process(const char **c, t_flag *flags, va_list args)
{
	ssize_t	count;

	count = 0;
	(*c)++;
	flags->precision = -1;
	ft_procest_flags(c, flags);
	ft_process_width(c, flags);
	ft_process_precision(c, flags);
	ft_process_type(**c, &count, flags, args);
	return (count);
}

int	ft_process_precision(const char **c, t_flag *flags)
{
	if (**c != '.')
		return (0);
	(*c)++;
	if (**c < '0' || **c > '9')
	{
		flags->precision = 0;
		return (1);
	}
	flags->precision = 0;
	while (**c >= '0' && **c <= '9')
		flags->precision = flags->precision * 10 + (*(*c)++ - '0');
	return (0);
}

void	ft_process_width(const char **c, t_flag *flags)
{
	flags->justify = ft_atoi(*c);
	while (**c >= '0' && **c <= '9')
		(*c)++;
}

void	ft_procest_flags(const char **c, t_flag *flags)
{
	while (**c == ' ' || **c == '#' || **c == '+' || **c == '0' || **c == '-')
	{
		if (**c == ' ')
			flags->space = 1;
		if (**c == '#')
			flags->hashtag = 1;
		if (**c == '+')
			flags->plus = 1;
		if (**c == '0')
			flags->zero = 1;
		if (**c == '-')
			flags->minus = 1;
		(*c)++;
	}
}

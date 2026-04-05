/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:57:38 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 15:45:47 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_null_char(t_flag *flags)
{
	ssize_t	count;
	ssize_t	tmp;

	count = 0;
	if (!flags->minus)
		count += ft_write_width(flags, flags->justify - 1, 0);
	tmp = ft_write(1, "\0", 1, flags);
	if (tmp == -1)
		return (-1);
	count += tmp;
	if (flags->minus)
		count += ft_write_width(flags, flags->justify - 1, 0);
	return (count);
}

size_t	ft_print_char(t_flag *flags, int arg)
{
	char	str[2];

	if (arg == 0)
		return (ft_print_null_char(flags));
	str[0] = (unsigned char)arg;
	str[1] = '\0';
	flags->zero = 0;
	return (ft_print_padded(str, flags));
}

size_t	ft_print_str(t_flag *flags, char *arg)
{
	size_t	count;
	char	*str;

	if (!arg && flags->precision >= 0 && flags->precision < 6)
		return (0);
	if (!arg)
		arg = "(null)";
	if (flags->precision >= 0)
		str = ft_substr(arg, 0, flags->precision);
	else
		str = ft_strdup(arg);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	count = ft_print_padded(str, flags);
	free(str);
	return (count);
}

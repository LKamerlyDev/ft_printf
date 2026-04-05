/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:45:25 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 18:10:05 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_build_digit_str(t_flag *flags, unsigned long arg, char c)
{
	char	*str;

	if ((flags->plus || flags->space || (long)arg < 0) && c != 'u')
		str = ft_itoa_with_sign((long)arg);
	else
		str = ft_itoa(arg);
	if (!str)
	{
		flags->errno = ALLOC_ERROR;
		return (NULL);
	}
	if (flags->space && !flags->plus && *str == '+')
		*str = ' ';
	return (str);
}

static char	*ft_apply_precision_digit(char *str, t_flag *flags,
		unsigned long arg)
{
	size_t	sign_len;
	size_t	num_len;
	char	*new_str;

	sign_len = (*str == '-' || *str == '+' || *str == ' ');
	num_len = ft_strlen(str) - sign_len;
	if (flags->precision == 0 && arg == 0)
	{
		free(str);
		str = ft_strdup("");
		if (!str)
		{
			flags->errno = ALLOC_ERROR;
			return (NULL);
		}
		sign_len = 0;
		num_len = 0;
	}
	new_str = ft_precision_pad(str, sign_len, num_len, flags->precision);
	if (!new_str)
	{
		flags->errno = ALLOC_ERROR;
		return (NULL);
	}
	return (new_str);
}

ssize_t	ft_print_digits(t_flag *flags, unsigned long arg, char c)
{
	char	*str;
	ssize_t	count;

	str = ft_build_digit_str(flags, arg, c);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	str = ft_apply_precision_digit(str, flags, arg);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	if (flags->precision >= 0)
		flags->zero = 0;
	count = ft_print_padded(str, flags);
	free(str);
	return (count);
}

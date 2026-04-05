/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:12:47 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 13:28:58 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_write_width(t_flag *flags, ssize_t len, int zero)
{
	ssize_t	count;
	char	c;

	count = 0;
	c = ' ';
	if (zero)
		c = '0';
	while (len-- > 0)
		count += ft_write(1, &c, 1, flags);
	return (count);
}

static ssize_t	ft_write_sign(t_flag *flags, char **str, size_t padding)
{
	ssize_t	count;

	count = ft_write(1, *str, 1, flags);
	(*str)++;
	count += ft_write_width(flags, padding, 1);
	return (count);
}

static ssize_t	ft_write_left(t_flag *flags, char *str, size_t padding)
{
	ssize_t	count;

	count = 0;
	while (*str)
		count += ft_write(1, str++, 1, flags);
	count += ft_write_width(flags, padding, 0);
	return (count);
}

static ssize_t	ft_write_right(char **str, t_flag *flags, size_t padding)
{
	ssize_t	count;

	count = 0;
	if (!ft_strncmp(*str, "0x", 2))
	{
		if (flags->plus)
			count += ft_write(1, "+", 1, flags);
		if (flags->zero)
		{
			count += ft_write(1, "0x", 2, flags);
			*str += 2;
			count += ft_write_width(flags, padding, flags->zero);
		}
		else
			count += ft_write_width(flags, padding, flags->zero);
		return (count);
	}
	if (flags->zero && (**str == '+' || **str == '-'))
		count += ft_write_sign(flags, str, padding);
	else
		count += ft_write_width(flags, padding, flags->zero);
	return (count);
}

ssize_t	ft_print_padded(char *str, t_flag *flags)
{
	ssize_t	count;
	size_t	padding;
	char	*tmp;

	if (!str)
		return (ft_write(1, "(null)", 6, flags));
	count = 0;
	padding = 0;
	if (flags->justify > ft_strlen(str))
		padding = flags->justify - ft_strlen(str);
	tmp = str;
	if (!flags->minus)
		count += ft_write_right(&tmp, flags, padding);
	while (*tmp)
		count += ft_write(1, tmp++, 1, flags);
	if (flags->minus)
		count += ft_write_left(flags, tmp, padding);
	return (count);
}

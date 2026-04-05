/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:41:18 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 17:41:55 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_set_prefix(char *str, t_flag *flags, unsigned int arg,
		const char *prefix)
{
	if (flags->hashtag && arg != 0)
	{
		ft_strlcat(str, prefix, 3);
		flags->hashtag = 2;
		return (2);
	}
	return (0);
}

char	*ft_hexa_build_str(t_flag *flags, unsigned long long arg,
		const char *prefix, const char *base)
{
	char	*str;
	int		offset;

	str = ft_calloc(sizeof(unsigned long long) * 2 + 3, 1);
	if (!str)
	{
		flags->errno = ALLOC_ERROR;
		return (NULL);
	}
	offset = ft_set_prefix(str, flags, arg, prefix);
	putnbr_base((unsigned long long)arg, str, offset, base);
	return (str);
}

static ssize_t	ft_print_hexa_core(t_flag *flags, unsigned int arg,
		const char *prefix, const char *base)
{
	ssize_t	count;
	char	*str;
	size_t	prefix_len;

	str = ft_hexa_build_str(flags, arg, prefix, base);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	if (!(flags->hashtag && arg != 0))
		flags->hashtag = 0;
	if (arg == 0 && flags->precision == 0)
	{
		str = ft_handle_zero_precision(str);
		if (!str)
			return (flags->errno = ALLOC_ERROR);
	}
	prefix_len = (size_t)(flags->hashtag == 2) * 2;
	str = ft_precision_pad(str, prefix_len, ft_strlen(str) - prefix_len,
			flags->precision);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	if (flags->precision >= 0)
		flags->zero = 0;
	count = ft_print_padded(str, flags);
	free(str);
	return (count);
}

size_t	ft_print_hexa_digits_lower(t_flag *flags, unsigned int arg)
{
	return (ft_print_hexa_core(flags, arg, "0x", HEX_BASE_LOWER));
}

size_t	ft_print_hexa_digits_upper(t_flag *flags, unsigned int arg)
{
	return (ft_print_hexa_core(flags, arg, "0X", HEX_BASE_UPPER));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:49:18 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 17:20:36 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putnbr_base(unsigned long n, char *buffer, int idx, const char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (n / base_len != 0)
		idx = putnbr_base(n / base_len, buffer, idx, base);
	buffer[idx] = base[n % base_len];
	return (++idx);
}

int	putnbr_base_signed(long n, char *buffer, int idx, const char *base)
{
	if (n < 0)
	{
		buffer[idx++] = '-';
		n = -n;
	}
	return (putnbr_base((unsigned long)n, buffer, idx, base));
}

size_t	ft_print_ptr(t_flag *flags, void *ptr)
{
	unsigned long long	num;
	char				*str;
	size_t				count;
	size_t				num_len;

	num = (unsigned long long)ptr;
	if (num == 0)
		return (ft_print_padded("(nil)", flags));
	flags->hashtag = 1;
	str = ft_hexa_build_str(flags, num, "0x", HEX_BASE_LOWER);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	num_len = ft_strlen(str) - 2;
	str = ft_precision_pad(str, 2, num_len, flags->precision);
	if (!str)
		return (flags->errno = ALLOC_ERROR);
	if (flags->precision >= 0)
		flags->zero = 0;
	count = ft_print_padded(str, flags);
	free(str);
	return (count);
}

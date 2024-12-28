/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_bx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjell <kjell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:22 by krenken           #+#    #+#             */
/*   Updated: 2024/12/28 14:46:15 by kjell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_speficier_bx(unsigned int num)
{
	int		len;
	char	*big_hex;

	big_hex = "0123456789ABCDEF";
	len = 0;
	if (num > 15)
	{
		len += ft_speficier_bx(num / 16);
	}
	len += ft_printchar(big_hex[num % 16]);
	return (len);
}

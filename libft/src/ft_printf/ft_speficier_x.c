/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_speficier_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjell <kjell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:41:30 by krenken           #+#    #+#             */
/*   Updated: 2024/12/28 14:46:34 by kjell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_speficier_x(unsigned int num)
{
	int		len;
	char	*small_hex;

	small_hex = "0123456789abcdef";
	len = 0;
	if (num > 15)
	{
		len += ft_speficier_x(num / 16);
	}
	len += ft_printchar(small_hex[num % 16]);
	return (len);
}

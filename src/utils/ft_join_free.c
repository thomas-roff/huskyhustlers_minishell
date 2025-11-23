/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:53:40 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/23 17:54:15 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"

char	*ft_join_free(char *temp, char *str)
{
	char	*res;

	res = ft_strjoin(temp, str);
	free(temp);
	return (res);
}

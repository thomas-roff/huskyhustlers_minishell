/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:14:55 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/30 12:14:59 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
        char *inpt;

        int i = 0;

        while ( i < 10 )
        {
                inpt = readline("Enter text: ");
                add_history(inpt);
                printf("%s", inpt);
                printf("\n");
                ++i;
        }

        return 0;

}

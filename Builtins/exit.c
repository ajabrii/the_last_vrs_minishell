/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:01 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/25 15:36:57 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void    ft_exit(int ex)
{
    if (neobash.level > 1)
    {
        neobash.level -= 1;
        update_env("SHLVL", ft_itoa(neobash.level));
    }
    // ft_free_all();
    printf("exit\n");
    exit(ex);
}

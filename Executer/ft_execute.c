/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/01 11:33:32 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_executer()
{
    if (neobash.tree->type == CMD_N && !ft_strncmp(neobash.tree->args, "env", 3))
        ft_env(neobash.envl);
    if (neobash.tree->type != CMD_N && !ft_strncmp(neobash.tree->left->args, "env", 3))
        ft_env(neobash.envl);
    if (neobash.tree->type == CMD_N && !ft_strncmp(neobash.tree->args, "exit", 4))
        ft_exit(0);
    if (neobash.tree->type != CMD_N && !ft_strncmp(neobash.tree->left->args, "exit", 4))
        ft_exit(1);
    return;
}

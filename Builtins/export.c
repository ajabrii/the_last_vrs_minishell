#include "../Header/headers.h"


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:16:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 15:57:27 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static int	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}


void	print_ex(t_env *env)
{
	while (env)
	{
			printf("declare -x ");
			printf("%s", env->key);
			if (env->value)
				printf("=\"%s\"\n", env->value);
			else
				printf("\n");
		env = env->next;
	}
}


int	parse_key(char *str)
{
	int	i;

	i = 0;
	neobash.count = 0;
	// printf("str is ::%s::\n", str);
	if (!ft_isalpha(str[i]))
		return (1);
    i++;
	while (str[i] && str[i] != '=' && str[i] == ' ')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	neobash.count = 0;
	// printf("string is ::%s\n", str);
	while (str[i])
	{
		if (str[i] == '=' || str[i] == ' ')
		{
			neobash.count = i + 1;
			// printf ("here\n");
			return (ft_substr(str, 0, i));
		}
		i++;
	}
	neobash.count = i;
	// printf("i is ::%i\n", neobash.count);
	return (ft_strdup(str));
}

bool search_env(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(tmp->key)))
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

char	*sub_value(char *str)
{
	int	i = 0;
	int s = 0;

	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=')
		{
			s = i + 1;
			while (str[i])
			{
				i++;
				if (!str[i])
				{
					neobash.count = i;
					return (ft_substr(str, s, i - s)); // + 1 for space after '='
				}
				else if (str[i] == ' ')
				{
					neobash.count = i + 1;
					return (ft_substr(str, s, i - s));
				}
			}
		}
		i++;
	}
	return (NULL);
}

int	ft_export(char *s)
{
	int		i;
	int		exit;
	char	*key;
	char	*ss;

	exit = 0;
    i = 7;
	if (!(s[i - 1]))
	{
		print_ex(neobash.envl);
		return (1);
	}
	while (&s[i] && s[i])
	{
		printf("entry is ::%s\n", &s[i]);
		if (parse_key(&s[i]))
			exit = ft_export_err_msg(&s[i]);
		else
		{
			key = get_key(&s[i]);
			if (search_env(key))
			{
				update_env(key, sub_value(&s[i]));
			}
			else
			{
                ss = sub_value(&s[i]);
				exp_back(exp_new(key, ss));
			}
		}
		printf("key is ::%s |||| value is ::%s\n", key, ss);
		i += neobash.count;
		printf("ends in : %i \n", i);
		// free kay and ss here;
		// i have to incremenet here to get the new statmenet
	}
    return(exit);
}
// "hello = ok oki =" --> hello=ok oki == and that's error!!!
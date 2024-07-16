/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:58:07 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/03 18:49:59 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

// size_t	ft_strlen(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i])
// 		i++;
// 	return (i);
// }

// static char	*ft_while(char *ptr, const char *str1, const char *str2)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str1[i])
// 	{
// 		ptr[i] = str1[i];
// 		i++;
// 	}
// 	while (str2[j])
// 	{
// 		ptr[i] = str2[j];
// 		j++;
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*strs;
// 	int		t_len;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	t_len = ft_strlen(s1) + ft_strlen(s2);
// 	strs = malloc(t_len + 1);
// 	if (!strs)
// 		return (NULL);
// 	ft_while(strs, s1, s2);
// 	return (strs);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
// 	{
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

int skip(char *s)
{
    int i = 0;

    if (!ft_strncmp(s, "cd", 2))
        i += 2;
    while (s[i] && s[i] == ' ')
        i++;
    if (!s[i])
        return (0);
    return (i);
}

void bt_cd(char *s)
{
    int i;
    char *str;

    i = 0;
    i = skip(s);
    if (i == 0)
    {
        chdir("/home");
        update_env("OLDPWD", get_env_val("PWD"));
        update_env("PWD", "/home");
        return;
    }
    s += i;
    if (s[0] && s[0] == '~')
    {
        s++;
        str = ft_strjoin("/home", s);
        chdir(str);
        update_env("OLDPWD", get_env_val("PWD"));
        update_env("PWD", str);
        free(str);
        return;
    }
    else if(chdir(s) == -1)
    {
        perror("cd");
        return;
    }
    update_env("OLDPWD", get_env_val("PWD"));
    update_env("PWD", s);
    // printf("%s\n", s);
}

// int main(void)
// {
//     bt_cd("cd    /home/user");
// }

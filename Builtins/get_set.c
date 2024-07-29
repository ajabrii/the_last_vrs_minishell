# include "../Header/headers.h"

char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = neobash.envl;
	while (envlst)
	{
		if (!ft_strncmp(key, envlst->key, ft_strlen(envlst->key)))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value)
{
	t_env	*envlst;

	// printf("SHlvl\n");
	envlst = neobash.envl;
	while (neobash.envl)
	{
		if (!ft_strncmp(key, neobash.envl->key, ft_strlen(key)))
		{
			if (value)
				neobash.envl->value = ft_strdup(value);
			return ;
		}
		neobash.envl = neobash.envl->next;
	}
	neobash.envl = envlst;
}

t_env	*exp_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!value)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	exp_back(t_env *new)
{
	t_env	*curr;

	if (!neobash.envl)
	{
		neobash.envl = new;
		return ;
	}
	curr = neobash.envl;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

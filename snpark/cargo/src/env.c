#include "minishell.h"

t_env	*export(char *str, t_env *head, int	flag)
{
	int	i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		++i;
	if (!str[i])  
	// =이 없으면 멀쩡한 형식이 아님
		return(NULL);
	str[i] = '\0';
	if (!str[0]) 
	// "=something" 이라 key값이 없는 상황임
		return(NULL);
	//key 값이 중복되면? 
		// 그 key를 가진 구조체를 찾고, value 포인터를 free 한 후 새롭게 할당
	// key 값이 중복되지 않은 경우
	env = (t_env *)malloc(1);
	env->key = strdup(str);
	env->value = strdup(str + ++i);
	env->next = NULL;
	if (flag == 1)
		free(str);
	if (head == NULL)
		return (env);
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = env;
	return (head);
}

t_env	*parent_env(char **old_env)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (old_env[i] != NULL)
	{
		head = export(old_env[i], head, 0);
		++i;
	}
	return (head);
}

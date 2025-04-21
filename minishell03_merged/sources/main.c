#include "minishell.h"

int main(int argc, char **argv) {

    // Inlining functions from main.c
    if (g_signal != 6)
		ft_putstr("\b\b  \b\b");
	if (signo == SIGINT && (g_signal != 6))
	{
		ft_putstr("\n");
		if (g_signal != 5)
			prompt();
		g_signal = 2;
    if (g_signal == 5)
			ft_putstr("\b\b  \b\bQuit (core dumped)\n");
		g_signal = 3;
    int		err;
	t_error	error;
	t_split	*split;

	err = 0;
	split = parse_command(line, &error);
	if (!split)
	{
		print_error_parsing(error);
		if (error.num != SUCCESS)
			update_return(envl, ERROR);
    char	*line;

	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	line = NULL;
	g_signal = 0;
	update_return(envl, 0);
	prompt();
	while (reader(&line) > 0)
	{
		if (g_signal == 4)
			g_signal = 2;
		parse_and_exec(envl, line);
		g_signal = 0;
    t_list	*envl;
	int		exit_value;

	(void)argv;
	(void)argc;
	header();
	parse_env(&envl, env);
	exit_value = waiting_command(&envl);
	if (!exit_value)
		exit_value = get_return(envl);
	ft_lstclear(&envl, &free_entry);
	ft_putstr("exit\n");
	return (exit_value);

    // Inlining functions from cd.c
    char	*path_home;

	path_home = search_in_env(envl, "HOME");
	if (!path_home)
	{
		print_error("minishell: cd", NULL, 0, "HOME not set");
		return (ERROR);
    print_error("cd", path_home, errno, NULL);
		return (ERROR);
    char	*path_old;

	path_old = search_in_env(envl, "OLDPWD");
	if (!path_old)
	{
		print_error("minishell: cd", NULL, 0, "OLDPWD not set");
		return (ERROR);
    print_error("cd", path_old, errno, NULL);
		return (ERROR);
    int		err;
	char	*path;

	if (number_of_args(cmd->argv + cmd->offset) > 2)
	{
		print_error("minishell: cd", NULL, 0, "too many arguments");
		return (MISUSE);
    path = cmd->argv[cmd->offset + 1];
		errno = 0;
		if (ft_strcmp("-", path) == 0)
			return (cd_old(*envl));
		err = chdir(path);
		if (err)
		{
			print_error("cd", cmd->argv[cmd->offset + 1], errno, NULL);
			return (ERROR);

    // Inlining functions from echo.c
    while (args[i] && args[i + 1])
	{
		ft_putstr(args[i]);
		ft_putstr(" ");
		i++;
    int	i;

	i = 1;
	while ((cmd->args)[i] && (ft_strcmp((cmd->args)[i], "-n") == 0))
		i++;
	return (i);
    int		i;
	int		pid;

	(void)envl;
	i = option_echo(cmd);
	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_args(cmd->argv + cmd->offset, (i > 1), i);
		exit(SUCCESS);

    // Inlining functions from env.c
    ft_putstr("declare -x ");
	ft_putstr(entry.var);
	if (entry.value)
	{
		ft_putstr("=\"");
		ft_putstr(entry.value);
		ft_putstr("\"");
    ft_putstr(entry.var);
	ft_putstr("=");
	ft_putstr(entry.value);
	ft_putstr("\n");
    t_env	*entry;

	while (envl)
	{
		entry = (t_env *)envl->content;
		if (authorized_char(entry->var))
		{
			if (declare && entry->exported >= 1
				&& ft_strcmp(entry->var, "_") != 0)
				print_quoted(*entry);
			else if (!declare && entry->exported >= 2)
				print_unquoted(*entry);
    int		pid;

	add_env("_", ft_strdup("env"), envl, 1);
	pid = fork();
	if (pid == 0)
	{
		if (number_of_args(cmd->argv + cmd->offset) > 1)
		{
			print_error("env", NULL, 0,\
			"should be used without option and argument");
			exit(MISUSE);

    // Inlining functions from exit.c
    int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
    ft_putstr("exit\n");
	free_all(cmd->line, cmd->split);
	free_tree(cmd->root);
	ft_lstclear(envl, &free_entry);
    int	exit_value;

	if (number_of_args(cmd->argv) < 2)
	{
		exit_value = ft_atoi(search_in_env(*envl, "?begin"));
		free_exit(cmd, envl);
		exit(exit_value);
    free_exit(cmd, envl);
		print_error("minishell: exit", NULL, 0, "numeric argument required");
		exit(MISUSE);
    ft_putstr("exit\n");
		print_error("minishell: exit", NULL, 0, "too many arguments");
		return (ERROR);

    // Inlining functions from export.c
    if (number_of_args(cmd->argv + cmd->offset) <= 1)
		return (print_sorted(*envl, cmd));
	if (!cmd->is_subprocess)
		return (export_all(cmd->argv + cmd->offset + 1, envl, 2));
	else
		return (SUCCESS);

    // Inlining functions from export_sorted.c
    t_env	*ventry;
	t_env	*res;

	ventry = (t_env *)entry;
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->var = ft_strdup(ventry->var);
	res->value = NULL;
	if (ventry->value)
		res->value = ft_strdup(ventry->value);
	res->exported = ventry->exported;
	return (res);
    char	*str1;
	char	*str2;

	str1 = ((t_env *)data1)->var;
	str2 = ((t_env *)data2)->var;
	if (str1 && str2)
		return (ft_strcmp(str1, str2));
	return (0);
    t_list	*sorted;
	int		pid;

	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		sorted = ft_lstmap(envl, &copy_entry, &free_entry);
		ft_lstsort(&sorted, &cmp_entry);
		print_envl(sorted, 1);
		ft_lstclear(&sorted, &free_entry);
		exit(SUCCESS);

    // Inlining functions from pwd.c
    char	cwd[SIZE_PATH];
	int		pid;

	(void)envl;
	getcwd(cwd, SIZE_PATH);
	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		ft_putstr(cwd);
		ft_putstr("\n");
		exit(SUCCESS);

    // Inlining functions from unset.c
    t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
    int		i;
	int		ret;

	if (cmd->number <= 1)
		return (0);
	i = cmd->offset + 1;
	ret = SUCCESS;
	while (cmd->argv[i])
	{
		if (authorized_char(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
			unset_one(cmd->argv[i], *envl);
		else
		{
			invalid_identifier(cmd->argv[i], "unset", 1);
			ret = ERROR;

    // Inlining functions from declare.c
    t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ERROR);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (ERROR);
    t_list	*env;

	env = *envl;
	while (env)
	{
		if (ft_strcmp(((t_env *)env->content)->var, var) == 0)
		{
			if (value)
			{
				if (((t_env *)env->content)->value)
					free(((t_env *)env->content)->value);
				((t_env *)env->content)->value = value;
    char	*value;
	char	*tmp;

	tmp = ft_strchr(var, '=');
	if (tmp)
	{
		value = ft_strdup(tmp + 1);
		tmp[0] = '\0';
    int	i;
	int	err;

	i = 0;
	err = 0;
	while (vars[i])
	{
		err += export_one(vars[i], envl, exported);
		i++;

    // Inlining functions from env.c
    int	i;

	i = 0;
	list = list->next;
	while (list)
	{
		if (((t_env *)list->content)->exported >= exported)
			i++;
		list = list->next;
    int		size;
	int		i;
	char	**env;
	char	*tmp;

	size = size_of_list(envl, exported);
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	envl = envl->next;
	while (i < size)
	{
		if (((t_env *)envl->content)->exported >= exported)
		{
			tmp = ft_strjoin(((t_env *)envl->content)->var, "=");
			env[i] = ft_strjoin(tmp, ((t_env *)envl->content)->value);
			free(tmp);
			i++;

    // Inlining functions from replace.c
    char	*var;
	int		size;
	int		i;

	if (str[0] == '?')
		var = ft_strdup("?begin");
	else
	{
		size = ft_strlen(str);
		var = malloc((size + 1) * sizeof(char));
		if (!var)
			return (0);
		i = -1;
		while (++i < size && (ft_isalpha(str[i]) || str[i] == '_'))
			var[i] = str[i];
		var[i] = '\0';
    int		size;
	int		l;
	char	*current_var;

	l = ft_strlen(old);
	size = size_var(old + ++(*i), envl, &current_var);
	if (current_var)
		ft_strlcpy(dest, current_var, size + 1);
	if (old[*i] == '?')
		(*i)++;
	else
	{
		while (*i < l && (ft_isalpha(old[*i]) || old[*i] == '_'))
			(*i)++;
    int		l;
	int		res;
	int		i;

	l = ft_strlen(old);
	res = 0;
	i = 0;
	while (i < l)
	{
		if ((old[i] == '\"' || old[i] == '\\' || old[i] == '$')
				&& i > 0 && old[i - 1] == '\\')
		{
			fill[res - 1] = old[i];
			i++;
    if (i == 0 || old[i - 1] != '\\')
				res += replace_var(&i, old, envl, fill + res);

    // Inlining functions from update.c
    if (g_signal == 2)
		add_env("?begin", ft_itoa(130), envl, -1);
	else
		add_env("?begin", ft_itoa(err), envl, -1);
    return (ft_atoi(search_in_env(envl, "?begin")));
    char	*pwd;
	char	cwd[SIZE_PATH];

	pwd = search_in_env(*envl, "PWD");
	if (!pwd)
		return ;
	getcwd(cwd, SIZE_PATH);
	if (ft_strcmp(pwd, cwd) != 0)
	{
		add_env("OLDPWD", ft_strdup(pwd), envl, 1);
		add_env("PWD", ft_strdup(cwd), envl, 1);
    int	i;

	if (cmd)
		i = cmd->start - 1;
	else
	{
		i = 0;
		while (split[i].str)
			i++;
		i--;

    // Inlining functions from useful.c
    while (envl)
	{
		if (ft_strcmp(((t_env *)envl->content)->var, var) == 0)
			return (((t_env *)envl->content)->value);
		envl = envl->next;
    int		i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
    t_list	*current;
	void	*save;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = list_size(*begin_list);
	while (i < size)
	{
		j = 0;
		current = *begin_list;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				save = current->content;
				current->content = current->next->content;
				current->next->content = save;
    int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (line[i] && line[i] != c)
	{
		res[i] = line[i];
		i++;
    char	*env_var;
	char	*to_find;

	if (cut)
		to_find = ft_strcut(var, '=');
	else
		to_find = ft_strdup(var);
	env_var = ((t_env *)envl->content)->var;
	if (ft_strcmp(env_var, to_find) == 0)
	{
		free(to_find);
		return (1);

    // Inlining functions from args.c
    int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
    char	c;
	int		i;
	int		j;

	cmd->argv = malloc((cmd->nb_args + 1) * sizeof(char *));
	if (!(cmd->argv))
		return (error_msg(ALLOCATION_FAIL));
	i = 0;
	j = cmd->offset;
	while (j < cmd->nb_args)
	{
		c = cmd->seps[j];
		if (c == 'd' || c == '>' || c == '<')
			j++;
		else
		{
			cmd->argv[i] = cmd->args[j];
			i++;
    int	nb_arg;
	int	i;

	nb_arg = 0;
	i = -1;
	while (++i < cmd.number)
	{
		if (split[cmd.start + i].space)
			nb_arg++;
    int		i;
	int		j;
	int		end;
	char	*current;
	char	*save;

	i = -1;
	j = 0;
	while (++i < cmd.nb_args)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.number && !end)
		{
			save = current;
			current = ft_strjoin(cmd.args[i], split[cmd.start + j].str);
			free(save);
			end = split[cmd.start + j].space;
			j++;
    cmd->nb_args = count_arg(*cmd, split);
	cmd->args = malloc((cmd->nb_args + 1) * sizeof(char *));
	cmd->seps = malloc((cmd->nb_args + 1) * sizeof(char));
	if (!(cmd->args) || !(cmd->seps))
		return (-1);
	fill_args(*cmd, split);
	return (0);

    // Inlining functions from command.c
    if (ft_strcmp(str, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(str, "env") == 0)
		return (ENV);
	if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (-1);
    if (!cmd->argv[i])
		return (-1);
	cmd->builtin = is_builtin(cmd->argv[i]);
	if (cmd->builtin > -1)
		return (BUILTIN);
	if (ft_strchr(cmd->argv[i], '='))
		return (DECLARATION);
	if (is_path(cmd->argv[i]))
		return (EXECUTABLE);
	else
		return (EXECBIN);
    if (cmd->err)
		print_error(NULL, cmd->file_error, cmd->err, NULL);
	else
		print_error(NULL, NULL, 0,\
		"syntax error near unexpected token `newline'\n");
	return (ERROR);
    t_exec	exec_func[NB_TYPES];

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	if (g_signal)
		update_return(envl, 128 + g_signal);
	cmd->split = split;
	if (cmd->number == 0)
		return (SUCCESS);
	if (expand(cmd, *envl, split))
		return (ERROR);
	if (cmd->nb_args_tmp == 0)
		return (SUCCESS);
	if (update_in_out(cmd) < 0)
		return (error_in_out(cmd));
	if (create_tab_args(cmd))
		return (ERROR);
	if (cmd_type(cmd, 0) >= 0)
		return (exec_func[cmd_type(cmd, 0)])(cmd, envl);
	return (SUCCESS);

    // Inlining functions from execute.c
    int	ret;

	ret = err;
	if (status > 0)
	{
		if (status % 256 == 0)
			ret = status / 256;
		else
			ret = status;
    int	err;
	int	status;

	if (!tree)
		return (0);
	status = SUCCESS;
	err = execute_recursive(tree->left, split, envl);
	if (tree->info->type == CMD)
	{
		err = execute_cmd(tree->info, split, envl);
		close_unused_fd(tree->info);
		return (err);
    while (wait(&status) > 0)
			;
		update_last_arg(envl, tree->info, split);
		update_return(envl, return_value(status, err));
    int	i;

	i = 0;
	while (split[i].str)
		i++;
	if (i > 0 && split[i - 1].sep == ';')
	{
		split[i - 1].str = NULL;
		split[i - 1].sep = '\0';
    t_tree	*tree;
	int		status;
	int		err;

	status = SUCCESS;
	remove_last_semic(split);
	tree = create_tree(split, line);
	if (pipe_recursive(tree, split, envl))
	{
		free_tree(tree);
		print_error(NULL, NULL, TOOMANY, NULL);
		return (TOOMANY);

    // Inlining functions from file.c
    char	*tmp;

	tmp = ft_strjoin(to_join, "/");
	if (*file)
		free(*file);
	*file = ft_strjoin(tmp, cmd->argv[cmd->offset]);
	free(tmp);
    char	**path_list;
	char	*path;
	int		i;
	int		fd;

	*file = NULL;
	path = search_in_env(envl, "PATH");
	if (!path)
		return (ERROR);
	path_list = ft_split(path, ":=");
	fd = -1;
	i = 0;
	while (path_list[i] && fd < 0)
	{
		join_path(path_list[i], file, cmd);
		fd = open(*file, O_RDONLY);
		i++;
    close(fd);
		return (SUCCESS);

    // Inlining functions from fork.c
    int		pid;
	char	**argv;
	char	*to_exec;
	int		err;

	cmd->env = create_env_tab(envl, 0);
	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		errno = 0;
		argv = cmd->argv + cmd->offset;
		to_exec = cmd->args[cmd->offset];
		if (file)
			to_exec = file;
		err = execve(to_exec, argv, cmd->env);
		print_error(to_exec, NULL, errno, NULL);
		if (errno == 2)
			exit(NOTFOUND);
		else
			exit(CANTEXEC);

    // Inlining functions from pipe.c
    if (!tree)
		return ;
	if (out)
		tree->info->output = fd;
	else
		tree->info->input = fd;
	tree->info->is_subprocess = is_sub;
	fill_subtree_fd(tree->left, out, fd, is_sub);
    int	pfd[2];
	int	type;

	if (!tree)
		return (SUCCESS);
	type = tree->info->type;
	if (type == CMD)
		return (SUCCESS);
	if (type == SEMIC)
	{
		fill_subtree_fd(tree->right, 0, 0, 0);
		fill_subtree_fd(tree->right, 1, 1, 0);

    // Inlining functions from types.c
    t_exec	builtin[NB_BUILTIN];

	builtin[ECHO] = &ft_echo;
	builtin[CD] = &ft_cd;
	builtin[PWD] = &ft_pwd;
	builtin[EXPORT] = &ft_export;
	builtin[UNSET] = &ft_unset;
	builtin[ENV] = &ft_env;
	builtin[EXIT] = &ft_exit;
	return (builtin[cmd->builtin](cmd, envl));
    if (ft_strcmp(cmd->argv[cmd->offset], "./minishell") == 0)
		g_signal = 6;
	return (fork_and_exec(cmd, *envl, NULL));
    int		i;
	t_exec	exec_func[NB_TYPES];

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	i = 0;
	while (cmd->argv[i] && ft_strchr(cmd->argv[i], '='))
		i++;
	if (cmd->argv[i])
	{
		cmd->offset = i;
		return (exec_func[cmd_type(cmd, i)](cmd, envl));
    char	*file;
	int		err;

	if (open_executable(cmd, *envl, &file))
	{
		if (file)
			free(file);
		print_error(cmd->argv[cmd->offset], NULL, 0, "command not found");
		return (NOTFOUND);

    // Inlining functions from useful.c
    if (cmd->output != STDOUT)
	{
		close(STDOUT);
		dup(cmd->output);
    close(STDIN);
		dup(cmd->input);
    if (cmd->input != STDIN && cmd->input != -1)
		close(cmd->input);
	if (cmd->output != STDOUT && cmd->output != -1)
		close(cmd->output);
    int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && (s[0] != '_'))
		return (0);
	while (s[i] && (s[i] != '='))
	{
		if (!ft_isalnum(s[i]) && (s[i] != '_'))
			return (0);
		i++;
    int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '/')
			return (1);
		i++;

    // Inlining functions from expansion.c
    if (str[i] == '?')
		i++;
	else
	{
		while (i < l && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
    int		i;
	int		res;
	int		l;
	char	*value;

	l = ft_strlen(str);
	res = 0;
	i = 0;
	while (i < l)
	{
		if (str[i] == '$')
		{
			if (i > 0 && str[i - 1] == '\\')
				i++;
			else
			{
				res += size_var(str + ++i, envl, &value);
				i = skip_var(str, i, l);
    int		size_tot;
	char	*new;

	size_tot = expanded_size(curr.str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return ;
	fill_expanded(new, curr.str, envl);
	ft_lstadd_back(expansion, new_entry(new, curr.sep, curr.space));
	free(new);
    int		size_tot;
	int		i;
	char	**split;
	char	*new;

	size_tot = expanded_size(curr.str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return (ALLOCATION_FAIL);
	fill_expanded(new, curr.str, envl);
	split = ft_splitchar(new, ' ');
	free(new);
	i = 0;
	while (split[i])
	{
		if (split[i + 1])
			ft_lstadd_back(expansion, new_entry(split[i], ' ', 1));
		else
			ft_lstadd_back(expansion, new_entry(split[i], ' ', curr.space));
		i++;

    // Inlining functions from join.c
    int	nb_arg;
	int	i;

	nb_arg = 0;
	i = -1;
	while (++i < cmd.nb_args_tmp)
	{
		if (cmd.spaces_tmp[i])
			nb_arg++;
    int		i;
	int		j;
	int		end;
	char	*current;

	i = -1;
	j = 0;
	while (++i < cmd.nb_args)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.nb_args_tmp && !end)
		{
			cmd.args[i] = current;
			current = ft_strjoin(cmd.args[i], cmd.args_tmp[j]);
			free(cmd.args[i]);
			if (cmd.spaces_tmp[j])
				end = 1;
			j++;
    cmd->nb_args = count_arg(*cmd);
	cmd->args = malloc((cmd->nb_args + 1) * sizeof(char *));
	cmd->seps = malloc((cmd->nb_args + 1) * sizeof(char));
	if (!cmd->args || !cmd->seps)
		return (error_msg(ALLOCATION_FAIL));
	fill_args(*cmd);
	return (SUCCESS);

    // Inlining functions from main.c
    if (curr.sep == '\"')
	{
		expand_simple(expansion, curr, envl);
		return (SUCCESS);
    t_split	*curr;
	int		i;

	cmd->nb_args_tmp = list_size(expansion);
	cmd->args_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char *));
	cmd->seps_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(char));
	cmd->spaces_tmp = malloc((cmd->nb_args_tmp + 1) * sizeof(int));
	if (!cmd->args_tmp || !cmd->seps_tmp || !cmd->spaces_tmp)
		return (error_msg(ALLOCATION_FAIL));
	i = -1;
	while (++i < cmd->nb_args_tmp)
	{
		curr = expansion->content;
		cmd->args_tmp[i] = ft_strdup(curr->str);
		cmd->seps_tmp[i] = curr->sep;
		cmd->spaces_tmp[i] = curr->space;
		expansion = expansion->next;
    int	err;

	err = SUCCESS;
	if (curr.sep == '\"' || curr.sep == ' ')
		err = expand_then_add(expansion, curr, envl, *redir);
	else
		ft_lstadd_back(expansion, new_entry(curr.str, curr.sep, curr.space));
	if (err)
		return (ERROR);
	*redir = 0;
	if (is_redir(curr.sep))
		*redir = 1;
	return (SUCCESS);
    t_list	*expansion;
	int		i;
	int		redir;
	int		err;

	i = -1;
	expansion = NULL;
	err = SUCCESS;
	redir = 0;
	while (++i < cmd->number && !err)
		err = expand_one(&expansion, envl, split[cmd->start + i], &redir);
	if (err || list_to_tab(expansion, cmd))
	{
		ft_lstclear(&expansion, &free_expd);
		return (ERROR);

    // Inlining functions from useful.c
    if (c == '>' || c == 'd' || c == '<')
		return (1);
	return (0);
    t_split	*content;

	content = malloc(sizeof(t_split));
	content->str = ft_strdup(str);
	content->sep = sep;
	content->space = space;
	return (ft_lstnew(content));
    t_split	*to_free;

	to_free = (t_split *)expd;
	if (to_free)
	{
		free(to_free->str);
		free(to_free);

    // Inlining functions from count.c
    if (command[i] == '\"')
		return (DB_QUOTE);
	if (command[i] == '\'')
		return (QUOTE);
	if (is_operator(command[i]))
		return (OPERATOR);
	return (SPACE);
    t_parse	p;

	p.len_word = -1;
	p.sep = ' ';
	p.state = 0;
	p.nb = 0;
	return (state_reset(command, 0, &p));
    t_parse	p;

	p.len_word = 0;
	p.sep = ' ';
	p.state = 0;
	p.nb = 0;
	(void)state_reset(command, i, &p);
	*sep = p.sep;
	return (p.len_word);

    // Inlining functions from env.c
    char	*val;
	int		end;

	cont->value = NULL;
	end = ft_strlen(line);
	if (ft_strrchr(line, '=') != NULL)
	{
		val = ft_strchr(line, '=') + 1;
		end = ft_strlen(line) - ft_strlen(val) - 1;
		cont->value = ft_strdup(val);
    t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (NULL);
    t_env	*entry;

	entry = (t_env *)ventry;
	if (entry->var)
		free(entry->var);
	if (entry->value)
		free(entry->value);
	free(entry);
    t_list	*new;
	int		shlvl;
	int		i;

	i = 0;
	*envl = NULL;
	new = init_entry("?begin", -1);
	ft_lstadd_back(envl, new);
	while (env[i])
	{
		new = init_entry(env[i], 2);
		if (ft_strcmp(((t_env *)new->content)->var, "SHLVL") == 0)
		{
			shlvl = ft_atoi(((t_env *)new->content)->value);
			shlvl++;
			free(((t_env *)new->content)->value);
			((t_env *)new->content)->value = ft_itoa(shlvl);

    // Inlining functions from node.c
    info->nb_args = 1;
	info->nb_args_tmp = 0;
	info->env = NULL;
	info->spaces = NULL;
	info->file_error = NULL;
	info->err = 0;
	info->first_word = NULL;
	info->start_args = 0;
	info->offset = 0;
	info->args_tmp = NULL;
	info->seps_tmp = NULL;
	info->spaces_tmp = NULL;
	info->all = NULL;
	info->split = NULL;
    t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->type = type;
	info->input = 0;
	info->output = 1;
	info->start = i;
	info->number = number;
	info->builtin = 0;
	info->line = line;
	info->root = NULL;
	info->args = NULL;
	info->argv = NULL;
	info->seps = NULL;
	info->is_subprocess = 0;
	init_aux(info);
	return (info);
    t_tree	*new;
	t_info	*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(start, 0, number, line);
	new->left = NULL;
	new->right = NULL;
	new->info = new_info;
	return (new);
    t_tree		*new;
	t_info		*new_info;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new_info = init_node(i, type, 1, line);
	new->left = create_leave(start, i - start, line);
	new->right = NULL;
	new->info = new_info;
	return (new);

    // Inlining functions from parse.c
    int	j;

	j = -1;
	while (++j < i)
		free(split[j].str);
	free(split);
	return (-1);
    ft_strlcpy(word->str, cmd, word_len + 1);
	word->str[word_len + 1] = '\0';
	trim_seps(*word);
	word->space = 0;
    int		i;
	int		k;
	char	sep;
	int		size;
	int		word_len;

	size = ft_strlen(command);
	i = 0;
	k = 0;
	while (i < words)
	{
		while (ft_isspace(command[k]))
			k++;
		word_len = len_of_word(command, k, &sep);
		split[i].sep = sep_converter(sep, command, k);
		split[i].str = malloc((word_len + 2) * sizeof(char));
		if (!split[i].str)
			return (free_split(split, i));
		fill_one_word(&(split[i]), word_len, command + k);
		if (k + word_len < size && ft_isspace(command[k + word_len]))
			split[i].space = 1;
		k += word_len;
		i++;
    int		i;
	char	c;
	int		redir;

	i = -1;
	redir = 0;
	while (++i < words)
	{
		c = split[i].sep;
		if ((c == '>' || c == '<' || c == 'd' || c == ';' || c == '|'))
		{
			if (redir || (i == 0 && (c == ';' || c == '|')))
			{
				*token = c;
				return (1);
    int		words;
	t_split	*split;

	error->num = SUCCESS;
	trim_spaces(command);
	if (ft_strlen(command) == 0)
		return (NULL);
	words = nb_words(command);
	error->num = SYNTAX_QUOTES;
	if (words < 0)
		return (NULL);
	split = malloc((words + 1) * sizeof(t_split));
	error->num = ALLOCATION_FAIL;
	if (!split || fill_words(split, words, command) < 0)
		return (NULL);
	split[words].str = NULL;
	split[words].sep = '\0';
	error->num = SYNTAX_REDIR;
	if (add_virtual_spaces(split, words, &(error->token))
		&& free_split(split, words))
		return (NULL);
	return (split);

    // Inlining functions from redir.c
    if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->input != 0)
		close(cmd->input);
	errno = 0;
	cmd->input = open(cmd->args[i], O_RDONLY);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->input < 0)
		return (-2);
	return (0);
    if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->output != 1)
		close(cmd->output);
	errno = 0;
	cmd->output = open(cmd->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->output < 0)
		return (-2);
	return (0);
    if (++i >= cmd->nb_args)
		return (-1);
	if (cmd->output != 1)
		close(cmd->output);
	errno = 0;
	cmd->output = open(cmd->args[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->err = errno;
	cmd->file_error = cmd->args[i];
	if (cmd->output < 0)
		return (-2);
	return (0);
    int		i;

	i = -1;
	while (++i < cmd->nb_args)
	{
		if (cmd->seps[i] == '<' && fill_input(cmd, i))
			return (-1);
		else if (cmd->seps[i] == '>' && fill_out(cmd, i))
			return (-1);
		else if (cmd->seps[i] == 'd' && fill_app(cmd, i))
			return (-1);

    // Inlining functions from state.c
    if (is_operator(command[i]) == 3 && command[i + 1] == '>')
	{
		if (p->len_word == 0)
			p->len_word = 2;
		return (state_reset(command, i + 2, p));
    int	j;

	j = i;
	while (command[i] && command[i] != '\"')
	{
		if (command[i] == '\\')
		{
			i++;
			if (command[i] == '\0')
				return (-1);
    if (p->len_word == 0)
			p->len_word = i - j + 2;
		return (state_reset(command, i + 1, p));
    int	j;

	j = i;
	while (command[i] && command[i] != '\'')
		i++;
	if (command[i] == '\'')
	{
		if (p->len_word == 0)
			p->len_word = i - j + 2;
		return (state_reset(command, i + 1, p));
    int	j;

	j = i;
	while (command[i] && !is_spaceend(command[i]))
		i++;
	if (p->len_word == 0)
		p->len_word = i - j + 1;
	return (state_reset(command, i, p));
    int			l;

	l = ft_strlen(command);
	if (p->len_word > 0)
		return (is_state_ok(p));
	if (i >= l)
		return (is_state_ok(p));
	while (ft_isspace(command[i]))
		i++;
	if (command[i] == '\0')
		return (is_state_ok(p));
	p->state = new_state(command, i);
	p->sep = command[i];
	(p->nb)++;
	if (p->state == SPACE)
		return (state_space(command, i + 1, p));
	else if (p->state == QUOTE)
		return (state_quote(command, i + 1, p));
	else if (p->state == DB_QUOTE)
		return (state_db_quote(command, i + 1, p));
	else
		return (state_operator(command, i, p));

    // Inlining functions from tree.c
    if (c == '|')
		return (PIPE);
	if (c == ';')
		return (SEMIC);
	return (0);
    if (!tree)
		return ;
	tree->info->root = root;
	fill_root(tree->left, root);
	fill_root(tree->right, root);
    char	*last;

	if (i > 0)
	{
		last = split[i - 1].str;
		return (last[ft_strlen(last) - 1] == '\\');
    if (last_node)
		last_node->right = create_leave(i[1], i[0] - i[1], line);
	if (!(*tree))
		*tree = create_leave(0, i[0], line);
	fill_root(*tree, *tree);
    t_tree	*tree;
	t_tree	*last_node;
	t_tree	*new_node;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	new_node = NULL;
	tree = NULL;
	while (split[i[0]].str)
	{
		last_node = new_node;
		if (is_node(split[i[0]].sep) && !previous_end_with_slash(split, i[0]))
		{
			new_node = create_node(i[0], is_node(split[i[0]].sep), i[1], line);
			if (!tree)
				tree = new_node;
			if (last_node)
				last_node->right = new_node;
			i[1] = i[0] + 1;

    // Inlining functions from trim.c
    int	l;
	int	i;

	l = ft_strlen(s);
	i = l - 1;
	while (i >= 0 && ft_isspace(s[i]))
	{
		s[i] = '\0';
		i--;
    int	i;
	int	l;

	if (split.sep == '\'' || split.sep == '\"')
	{
		i = 0;
		l = ft_strlen(split.str);
		while (i + 2 < l)
		{
			split.str[i] = split.str[i + 1];
			i++;

    // Inlining functions from useful.c
    if (c == '<' || c == '|' || c == '=' || c == ';' || c == '\'' || c == '\"')
		return (c);
	if (c == '>')
	{
		if (command[k + 1] == '>')
			return ('d');
		return (c);
    if (c == '<' || c == '|')
		return (1);
	if (c == '=' || c == ';')
		return (2);
	if (c == '>')
		return (3);
	return (0);
    if (ft_isspace(c) || is_operator(c) || c == '\'' || c == '\"')
		return (1);
	return (0);
    if (p->state != OPERATOR || p->sep == '=' || p->sep == ';')
		return (p->nb);
	return (-1);
    if (i > 0)
		split[i - 1].space = 1;
	split[i].space = 1;

    // Inlining functions from errors.c
    if (error.num == SUCCESS)
		return ;
	ft_putstr_fd("minishell: ", STDERR);
	if (error.num == SYNTAX_QUOTES)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR);
	else if (error.num == SYNTAX_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		if (error.token == 'd')
			ft_putstr_fd(">>", STDERR);
		else
			ft_putchar_fd(error.token, STDERR);
		ft_putstr_fd("'\n", STDERR);
    if (!error)
		ft_putstr_fd("minishell: ", STDERR);
	if (exe)
	{
		ft_putstr_fd(exe, STDERR);
		ft_putstr_fd(": ", STDERR);
    ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
    ft_putstr_fd("minishell: ", STDERR);
	if (func && exported)
	{
		ft_putstr_fd(func, STDERR);
		ft_putstr_fd(": ", STDERR);
    ft_putstr_fd("minishell: ", STDERR);
	if (error == ALLOCATION_FAIL)
		ft_putstr_fd("allocation failed\n", STDERR);
	else if (error == FORK_FAIL)
		ft_putstr_fd("fork failed\n", STDERR);
	return (ERROR);
    ft_putstr_fd("minishell: ", STDERR);
	if (error == AMBIGUOUS_REDIR)
	{
		ft_putstr_fd(info, STDERR);
		ft_putstr_fd(": ambiguous redirect\n", STDERR);

    // Inlining functions from free.c
    int	i;

	(void)line;
	if (line)
		free(line);
	if (!split)
		return ;
	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
    int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
    ft_lstclear(words, &free);
	ft_lstclear(seps, &free);
	ft_lstclear(spaces, &free);
    if (cmd->args)
		free_tab(cmd->args);
	if (cmd->argv)
		free(cmd->argv);
	if (cmd->env)
		free_tab(cmd->env);
	if (cmd->seps)
		free(cmd->seps);
	if (cmd->spaces)
		free(cmd->spaces);
	if (cmd->args_tmp)
		free_tab(cmd->args_tmp);
	if (cmd->seps_tmp)
		free(cmd->seps_tmp);
	if (cmd->spaces_tmp)
		free(cmd->spaces_tmp);
    if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->info)
	{
		free_cmd(tree->info);
		close_unused_fd(tree->info);
		free(tree->info);

    // Inlining functions from prompt.c
    char	cwd[SIZE_PATH];

	getcwd(cwd, SIZE_PATH);
	ft_putstr("\033[1;36mmini@shell \033[0;36m");
	ft_putstr(cwd);
	ft_putstr("\033[0m$ ");
    ft_putstr("\033[1;36m  __  __ _       _     _          _ _\n");
	ft_putstr(" |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
	ft_putstr(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	ft_putstr(" | |  | | | | | | \\__ \\ | | |  __/ | |\n");
	ft_putstr(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n");

    // Inlining functions from reader.c
    char	*new_line;
	int		l;
	int		i;

	if (c == '\n')
		return (line);
	if (reset || g_signal == 2)
	{
		g_signal = 4;
		l = 0;
    char	*empty;

	empty = malloc(sizeof(char));
	if (!empty)
		return (empty);
	empty[0] = '\0';
	return (empty);
    if (c == '\n')
	{
		if (ft_strlen(*line) > 0 && (*line)[ft_strlen(*line) - 1] == '\\')
			(*line)[ft_strlen(*line) - 1] = '\0';
		else
		{
			*reset = 1;
			return (1);
    int	size;

	if (!line)
		return (-1);
	*line = malloc_empty_string();
	if (!(*line))
		return (-1);
	size = read(0, c, 1);
	return (size);
    static char	c;
	static int	size;
	static int	reset;

	size = error_and_first_read(line, &c);
	if (size < 0)
		return (-1);
	while (size >= 0)
	{
		if (should_quit(size, *line))
			break ;
		else if (size == 0)
			size = read(0, &c, 1);
		else
		{
			if (ignore_escaped(c, line, &reset))
				return (1);
			reset = 0;
			*line = join_realloc(*line, c, reset);
			if (!(*line))
				return (-1);
			size = read(0, &c, 1);

    // Inlining functions from reader_useful.c
    if (size == 0 && g_signal != 3
		&& (!line || ft_strlen(line) == 0 || g_signal == 2))
		return (1);
	return (0);

    return 0;
}
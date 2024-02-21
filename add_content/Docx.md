
### CAPTIONS

🎯	 -	 Prority
🗿	 -	 Nailed it baby !
🚧	 -	 Waiting for mate
⏳	-	In progress
🧪	 - 	 Benchmarking...
✅	-	Complete

### JCUZIN's part
**Functions**
	⏳ - Redirections:
	|	⏳ - Pipe 					[Redirect -1_Out 0_In]
	|	| 🧪 - Unique pipe
	|	| 		✅ -  Parsing part
	|	| 		🧪 -  Execute part
	|	| 🧪 - Multiple pipes
	|	| 		✅ -  Parsing part
	|	| 		🧪 -  Execute part
	|	| 🧪 - Consecutve pipes
	|	| 		✅ -  Parsing part
	|	|		🧪 -  Execute part
	|	\_
	|
	|	⏳ - File descriptor
	|	|	✅ - <			[take file descriptor as input]
	|	|					 
	|	|	✅ - >			[take file descriptor as output]
	|	|						
	|	|	⏳ - <<			[Heredoc]
	|	|
	|	|	✅ - >>			[Redirect output in no overwrite mode]
	|	\_
	\_  

**Features**	
		✅ - ""							[Double Quote]
		✅ - ''							[Simple Quote]

**Optionnal**	
		🚧 - $_							 [expand to exit status of most recently executed foreground pipeline]

**Manual cases**
	- Quotes cancelled out when placed side-by-side
			echo "xx"    "cc" ---> xx cc
			echo "xx""cc" ---> xxcc

### DOCUMENTATION

	- https://www.codequoi.com/pourquoi-je-necris-plus-darticles-sur-les-projets-de-42/#comments

### TESTS

< make cat -e | ls | wc -l | echo "     moustiques dans   ta   bouches   " > out

<makefile cat -e | wc -l <<wesh | ls -la -la > shesh

	`                "   test   '  "   test  ' `

$ ls -la "args1" "arg2" | cat -e "args1" "arg2" | ls -la -l -l "args1" <<HDDELIM >> "arg2"
$ test1
$ test2
$ HDDELIM
$

cat -e "t1" <<hd "t2"

cat -e <<hd <<hd <<hd

< Makefile ls | cat -e > out

POUR TESTER LA PIPELINE

	echo "just two of us" | cat -e

	echo $USER $?USERR

	EXPORT ? (env trie + mise en page particuliere)

	export _1 (marche sur bash, pas sur le votre)

	exit OK -> verif %256 ?

	cat Makefile>out (ecrit sur 1); toutes les redirections out

	gestion des quotes KO

















































int	get_type(char *data)
{
	int		type;

	type = _TOK_EMPTY;
	if (!data)
		return (type);
	if (find_str_in_str(data, "<") != -1)
	{
		type = _TOK_INFILE;
		if (find_str_in_str(data, "<<") != -1)
			type = _TOK_HEREDOC;
		if (ft_strlen(data) > 1)
			str_edit(&data, "<", "");
	}
	if (find_str_in_str(data, ">") != -1)
	{
		type = _TOK_OUTFILE;
		if (find_str_in_str(data, ">>") != -1)
			type = _TOK_OUTFILE_APP;
		if (ft_strlen(data) > 1)
			str_edit(&data, ">", "");
	}
	return (type);
}

t_cmd	*get_redirection(t_cmd *cmd, t_lst *list)
{
	int		err;

	err = 0;
	db_printf("\n\nGet_Redirection\n", FE_BOL);
	db_display_list(list, "Key_words");
	while (list && !err)
	{
		if (list->id > 0)
		{
			if (get_type(list->data) == _TOK_INFILE)
				err += set_infile(list->next->data \
				, &cmd->meta.infile, 0);
			if (get_type(list->data) == _TOK_OUTFILE)
				err += set_outfile(list->next->data \
				, &cmd->meta.infile, 0);
			if (get_type(list->data) == _TOK_OUTFILE_APP)
				err += set_outfile(list->next->data \
				, &cmd->meta.infile, 1);
		}
		list = list->next;
	}
	return (cmd);
}


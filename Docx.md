
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

if (heredoc_check(token))
	command->command.full = heredocument(command);


	`                "   test   '  "   test  ' `

ls -la "args1" "arg2" | cat -e "args1" "arg2" | ls -la -l -l "args1" "arg2"

cat -e "t1" <<hd "t2"

cat -e <<hd <<hd <<hd
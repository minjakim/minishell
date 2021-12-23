make -C ../../ > /dev/null
cp ../../minishell .
chmod 755 minishell

function exec_test()
{
	test1=$(./minishell -c "$@" )
	es_1=$?
	test2=$(bash -c "$@" )
	es_2=$?
	if [ "$test1" == "$test2" ] && [ "$es_1" == "$es_2" ]; then
		printf "ok"
	else
		printf "fail"
	fi
	printf "\t\ttest case : $@\n"
	printf "\t\toutput : [$test1]\n"
	printf "\t\texit satus : $es_1\n"
	if [ "$test1" != "$test2" ]; then
		echo
		echo
		printf "Your output : \n$test1\n"
		printf "Expected output : \n$test2\n"
	fi
	if [ "$es_1" != "$es_2" ]; then
		echo
		echo
		printf "Your exit status : $es_1\n"
		printf "Expected exit status : $es_2\n"
	fi
	sleep 0.1
}

printf "start"
printf "\n\n\n"

printf "simple Command\n"
exec_test /bin/ls
exec_test /bin/echo
exec_test /bin/pwd
exec_test /bin/date
printf "\n\n"

printf "Arguments & history\n"
exec_test '/bin/ls /'
exec_test '/bin/ls .'
exec_test '/bin/ls ..'
exec_test '/bin/echo hello'
exec_test '/bin/echo world'
printf "\n\n"

printf "echo\n"
exec_test 'echo'
exec_test 'echo -n'
exec_test 'echo world'
exec_test 'echo merry'
exec_test 'echo merry christmas'
exec_test 'echo hello world merry christmas'
exec_test 'echo hllo                             world                                          merry                                           christmas'
exec_test 'echo -n hello                                world                                     merry                     christmas'
exec_test 'echo "hello"world"'"merry"'"christmase'
printf "\n\n"

printf "exit\n"
exec_test 'exit'
exec_test 'exit 0'
exec_test 'exit 1'
exec_test 'exit -1'
exec_test 'exit 255'
exec_test 'exit hello'
exec_test 'exit 0 0'
exec_test 'exit hello world'
exec_test 'exit 0 hello'
exec_test 'exit hello 0'
exec_test 'exit 999999'
exec_test 'exit 999999999999999'
exec_test 'exit 000000000000000'
exec_test 'exit 3.141592'
echo
echo

printf "Return value of a process\n"
exec_test '/bin/ls'
exec_test 'qqq'
exec_test '*/'
exec_test '/bin/ls qqweqweqeqweqq'
echo
echo

printf 'Double Quotes\n'
exec_test 'echo "cat lol.c | cat > lol.c"'
exec_test 'echo "hello                                                              world"'
exec_test 'echo               "hello"                                               "world"'
exec_test '"echo" hello'
echo
echo

printf "cd\n"
exec_test 'cd . && pwd '
exec_test 'cd .. && pwd '
exec_test 'cd / && pwd '
exec_test 'cd - && pwd  '
exec_test 'cd qwe'
exec_test 'cd asd'
exec_test 'cd qwe'
exec_test 'unset OLDPWD && cd -'
exec_test 'unset HOME && cd -'
echo
echo

printf "Pipes"
exec_test 'echo hello | cat'
exec_test 'env | gerp PWD'


printf "Enviroment Variable\n"
exec_test 'echo $USER'
exec_test 'echo $HOME'
exec_test 'echo $123'
exec_test 'echo $USER.qwe'
exec_test 'echo $USERqwe'
echo
echo

printf "Bonus\n"
printf "And, Or\n"
exec_test 'echo hello && echo world'
exec_test 'echo hello || echo world'
exec_test '42 && echo 42 is command'
exec_test '42 || echo 42 is not command'
echo
echo
printf "WildCard\n"
exec_test 'echo *'
exec_test 'echo .*'
exec_test 'echo */'
echo
echo



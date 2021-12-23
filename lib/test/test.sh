RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

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
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	echo
	echo
	echo -n "press any key"
	echo
	echo
	echo
	read
	clear
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



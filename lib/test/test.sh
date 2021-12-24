#!/bin/bash

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
chmod 755 ../../minishell

function nl()
{
	for ((i = 0; i < $1; ++i))
	do
		echo
	done
}

function pf()
{
	printf $@
}

function pt()
{
	clear
	nl 2
	printf $1
	nl 2
}

function test()
{
	test1=$(../../minishell -c "$1" )
	es_1=$?
	test2=$(/bin/bash -c "$1" )
	es_2=$?
	if [ "$test1" == "$test2" ] && [ "$es_1" == "$es_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$1\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		nl 2
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		nl 2
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	nl 2
	sleep 1
}

pt "start"

pt "simple Command"
test '/bin/ls'
test '/bin/echo'
test '/bin/pwd'
test '/bin/date'

pt "Arguments & history"
test '/bin/ls /'
test '/bin/ls .'
test '/bin/ls ..'
test '/bin/echo hello'
test '/bin/echo world'

pt "echo"
test 'echo'
test 'echo -n'
test 'echo world'
test 'echo merry'
test 'echo merry christmas'
test 'echo hello world merry christmas'
test 'echo hllo           world             merry                                           christmas'
test 'echo -n hello              world                      merry                     christmas'
test 'echo "hello"world"'"merry"'"christmase'

pt "exit"
test 'exit'
test 'exit 0'
test 'exit 1'
test 'exit -1'
test 'exit 255'
test 'exit hello'
test 'exit 0 0'
test 'exit hello world'
test 'exit 0 hello'
test 'exit hello 0'
test 'exit 999999'
test 'exit 999999999999999'
test 'exit 000000000000000'
test 'exit 3.141592'

pt "Return value of a process"
test '/bin/ls'
test 'qqq'
test '*/'
test '/bin/ls qqweqweqeqweqq'

pt 'Double Quotes'
test 'echo "cat lol.c | cat > lol.c"'
test 'echo "hello                                                              world"'
test 'echo               "hello"                                               "world"'
test '"echo" hello'

pt "cd"
test 'cd . && pwd '
test 'cd .. && pwd '
test 'cd / && pwd '
test 'cd - && pwd  '
test 'cd asd'
test 'cd qwe'
test 'unset OLDPWD && cd -'
test 'unset HOME && cd'

pt "Pipes"
test 'echo hello | cat'
test 'env | gerp PWD'

pt "Enviroment Variable"
test 'echo $USER'
test 'echo $HOME'
test 'echo $USER.qwe'
test 'echo $USERqwe'

pt "Bonus"

pt "And, Or"
test 'echo hello && echo world'
test 'echo hello || echo world'
test '42 && echo 42 is command'
test '42 || echo 42 is not command'

pt "WildCard"
test 'echo *'
test 'echo .*'
test 'echo */'





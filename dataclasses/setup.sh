#!/bin/sh

error(){
	printf "\033[35mError:\t\033[31m${1}!\033[0m\n"
	exit 1
}

_python="$(command -v python)"

if [ ! -z "${_python}" ];
then
	echo "USING: $(${_python} -V)"
	_src=$(command -v pip)
	[ ! -z "${_src}" ] && pip install -r requirements.txt || error "Unable to find pip3 command"
else
	error "No Python program is installed"
fi

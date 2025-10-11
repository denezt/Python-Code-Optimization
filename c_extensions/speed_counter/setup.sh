#!/bin/bash -x

set -eu

error(){
	printf "\033[35mError:\t\033[31m${1}\033[0m\n"
	exit 1;
}

env_name="sc_venv"
[ -d "${env_name}" ] && rm -rfv "${env_name}"
python3 -m venv "${env_name}"
[ -e "${env_name}/bin/activate" ] && source ${env_name}/bin/activate || error "Missing or unable to find ${env_name}"
if [ -e "requirements.txt" ];
then
	( pip3 install -r requirements.txt )
else
	error "Unable to find the requirements.txt"
fi
deactivate

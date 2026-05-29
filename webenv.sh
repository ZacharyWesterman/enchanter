#!/usr/bin/env bash

if [ ! -d emsdk ]; then
    echo 'Installing EMSDK...'
    git clone https://github.com/emscripten-core/emsdk.git
    emsdk/emsdk install latest
    emsdk/emsdk activate latest
fi

#Create a new shell for the emsdk env

bash --rcfile <(echo '. ~/.bashrc
export PS1="(emsdk) $PS1"
EMSDK_QUIET=1 source emsdk/emsdk_env.sh
alias deactivate="exit"
echo -e "\e[34mVirtual environment active. To return to previous environment, press Ctrl-D, or type \`deactivate\` or \`exit\`.\e[0m"
')

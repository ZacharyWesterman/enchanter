#!/usr/bin/env bash

if [ ! -d emsdk ]; then
    echo 'Installing EMSDK...'
    git clone https://github.com/emscripten-core/emsdk.git
    emsdk/emsdk install latest
    emsdk/emsdk activate latest
fi

#Create a new shell for the emsdk env

bash --rcfile <(echo '. ~/.bashrc; export PS1="(emsdk) $PS1"; EMSDK_QUIET=1 source emsdk/emsdk_env.sh; echo "Virtual environment active. Ctrl-D or \`exit\` to return to regular env."')

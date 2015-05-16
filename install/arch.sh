#!/bin/bash
############################################################################

#  Veaml build script for Arch Linux

#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at http://mozilla.org/MPL/2.0/.
#  Copyright (c) 2014, David Charte fdavidcl@outlook.com

############################################################################

readonly OGDIR=`pwd`
readonly BASE="/tmp/veaml-install"
readonly OPSHINC="/usr/include/libopenshot"

is_dir() {
    local dir=$1
    [[ -d $dir ]]
}

gitget() {
    local repo=$1; shift
    local dir=$1; shift
    local args=$@
    
    local cur=`pwd`
    
    is_dir $dir \
        && ( \
            cd $dir \
                && git pull \
                && cd $cur
        ) \
        || git clone $args $repo $dir
}

print_welcome() {
    cat <<- EOF
Veaml build script for Arch Linux
========================================

This script will download and install dependencies
for the Veaml parser <http://fdavidcl.me/veaml>, then
build the parser itself.

EOF
}

install_libopenshot() {
    # Download and install libopenshot
    echo -e "\nDownloading and installing libopenshot and its dependencies..."
    sudo pacman -S libopenshot libopenshot-audio
}

patch_headers() {
    cd libopenshot/
    local patches=`ls *.patch`
    
    # Patch libopenshot
    echo -e "\nPatching libopenshot header files..."
    
    for patch in $patches
    do
        sudo patch $OPSHINC/`basename $patch .patch` $patch
    done
}

install_jsoncpp() {
    # Download and copy JsonCpp
    echo -e "\nDownloading JsonCpp..."
    gitget https://github.com/open-source-parsers/jsoncpp.git $BASE/jsoncpp -b master --single-branch \
        && sudo mkdir -p $OPSHINC/thirdparty/jsoncpp/ \
    	&& sudo cp -r $BASE/jsoncpp/include $OPSHINC/thirdparty/jsoncpp/ \
    	&& sudo cp -r $BASE/jsoncpp/src $OPSHINC/thirdparty/jsoncpp/
}

install_veaml() {
    # Download and install Veaml
    echo -e "\nCloning and installing Veaml..."
    gitget https://github.com/fdavidcl/veaml.git $BASE/veaml -b master --single-branch \
        && cd $BASE/veaml/patches \
        && patch_headers \
        && cd $BASE/veaml/build \
        && qmake \
        && make \
    	&& sudo make install
}

main() {
    print_welcome \
        && sleep 1 \
        && install_libopenshot \
        && install_jsoncpp \
        && install_veaml
}
main
##################################################
# Veaml build script for Arch Linux
##################################################

OGDIR=`pwd`
BASE="/tmp/veaml-install"
OPSHINC="/usr/include/libopenshot"

cat << EOF
Veaml build script for Arch Linux
========================================

This script will download and install dependencies
for the Veaml parser <http://fdavidcl.me/veaml>, then
build the parser itself.

EOF

sleep 1

# Download and install libopenshot
echo -e "\nDownloading and installing libopenshot and its dependencies..."
sudo pacman -S libopenshot libopenshot-audio

# Patch libopenshot
echo -e "\nPatching libopenshot header files..."


# Download and copy JsonCpp
echo -e "\nDownloading JsonCpp..."
git clone -b master --single-branch https://github.com/open-source-parsers/jsoncpp.git $BASE/jsoncpp \
    && sudo mkdir -p $OPSHINC/thirdparty/jsoncpp/ \
	&& sudo cp -r $BASE/jsoncpp/include $OPSHINC/thirdparty/jsoncpp/ \
	&& sudo cp -r $BASE/jsoncpp/src $OPSHINC/thirdparty/jsoncpp/ \


# Download and install Veaml
echo -e "\nCloning and installing Veaml..."
git clone -b master --single-branch https://github.com/fdavidcl/veaml.git $BASE/veaml \
    && cd $BASE/veaml/build \
    && qmake \
    && make \
	&& sudo make install

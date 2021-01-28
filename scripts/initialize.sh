
#!/bin/sh
export PATH=~/vcpkg:$PATH
[ ! -d ~/vcpkg ] && git clone https://github.com/microsoft/vcpkg ~/vcpkg &&
~/vcpkg/bootstrap-vcpkg.sh &&
vcpkg integrate $SHELL
vcpkg install $(cat dependencies.vcpkg)
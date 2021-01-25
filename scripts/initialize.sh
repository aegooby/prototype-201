
#!/bin/sh
vcpkg/bootstrap-vcpkg.sh
vcpkg/vcpkg integrate $SHELL
vcpkg/vcpkg install $(cat dependencies.vcpkg)
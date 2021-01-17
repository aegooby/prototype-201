
#!/bin/sh
cmake -B build -Wno-dev -D CMAKE_BUILD_TYPE=Debug &&
compdb -p build/ list > compile_commands.json &> /dev/null

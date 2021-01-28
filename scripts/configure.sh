
#!/bin/sh
cmake -B build -Wno-dev -D CMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" &&
cp -r build/compile_commands.json compile_commands.json

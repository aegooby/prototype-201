
#!/bin/sh
rm -rf build &&
rm -rf compile_commands.json &&
cmake -B build -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -Wno-dev &&
ln -s build/compile_commands.json compile_commands.json

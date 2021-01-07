
#!/bin/sh
rm -rf compile_commands.json &&
cmake -B build -Wno-dev &&
ln -s build/compile_commands.json compile_commands.json

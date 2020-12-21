
#!/bin/sh
rm -rf compile_commands.json &&
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 &&
ln -s build/compile_commands.json compile_commands.json

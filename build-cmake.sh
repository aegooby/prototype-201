
#!/bin/sh
cmake -B build -Wno-dev &&
compdb -p build/ list > compile_commands.json &> /dev/null

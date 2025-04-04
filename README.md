# Retree

A simple utility to recreate project structure from a `tree` utility file output.

e.g.

```tree
./
├── cabin-out
│   └── debug
│       ├── compile_commands.json
│       ├── Makefile
│       ├── retree
│       └── retree.d
│           └── main.o
├── cabin.toml
├── ex.tree
└── src
    └── main.cc

4 directories, 7 files
```

running `retree -f tree.txt -d /path/to/recreation` you will get the same directory structure.

## Tests

To run them:

```bash
bash ./tests/run-tests.sh
```

## Build steps

This project is simple and consists of just one executable, so `cabin` build system
and package-manager is used

### So, to build

```bash
cabin build --release && sudo mv cabin-out/release/retree /usr/local/bin/
```

### Or with cmake

```bash
cmake -B build/ -DCMAKE_BUILD_TYPE=Release . && cmake --build build/ && sudo mv ./build/retree /usr/local/bin
```

### Or, install binary (compiled only for linux amd64, glibc >= 2.27, inside that Dockerfile)

```bash
wget -O retree "https://github.com/Processor228/retree/releases/download/v0.1.1/retree"
chmod +x retree
sudo mv retree /usr/local/bin/
```

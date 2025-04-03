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

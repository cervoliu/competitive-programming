Personal competitive programming settings.


Features:

- Use **VS Code** as the default editor.
- Use **clang** as the default compiler, **LLDB** as the default debugger.
- Use dev container to unify coding environment and to sync with OJ environment.
- Use git modules to refer third-party headers or libraries.

## Usage:

You may need to manually configure the git hooks path for this repository,
if you'd like to reuse the provided hooks under `.githooks`.
```sh
git config core.hooksPath .githooks
```


---

To do:
- add `.clang-format` and `.clang-tidy`.
- add [CPL](https://github.com/dieram3/competitive-programming-library/tree/master) as submodule.
- add a problem info parser.
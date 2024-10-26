This directory lists some useful scripts for convenience.

The scripts are not intended to run manually.

- `code-snippets-format-converter.py` :
Automatically generates `.vscode/cpp.code-snippets` according to 
the customized cpp snippets under `../template/`.
A git pre-commit hook is written for this, but not yet being tracked by git.

- `atcoder-expander.py` :
Expand headers of `ac-library`. Useful when including atcoder-headers
but submiting to elsewhere.
A vscode task is written for this, see `.vscode/tasks.json`.

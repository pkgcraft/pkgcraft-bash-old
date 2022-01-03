# pkgcraft-bash

Various C-based bash plugins.

## Plugins

### Bash

- **profile**: benchmark bash functions

## Development

Developing pkgcraft-bash assumes that recent versions of meson and bash are
installed along with a standard C compiler.

Note that bash must be built with plugin support enabled and also have the
development files (.pc and headers) available on the system.

To build pkgcraft-bash, run the following commands:

```bash
meson setup build && meson compile -C build -v
```

## Usage

Plugin usage varies depending on what the plugin is meant for. See the
following example using the **profile** plugin.

```bash
# load plugin
enable -f build/src/profile.so profile

# profile a bash function or command
profile cmd arg1 arg2
```

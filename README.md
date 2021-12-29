# pkgcraft-bash

Various bash plugins that leverage pkgcraft's C API instead of being forced to
maintain duplicate functionality such as version parsing and comparisons in
bash. The canonical definition for many of the plugins comes from the [Package
Manager Specification][1] used by Gentoo.

## Plugins

### Pkgcraft (requires pkgcraft-c library)

- **has**: determine if a string is in a list of strings
- **ver_cut**: output version substrings
- **ver_rs**: perform version string substitutions
- **ver_test**: perform version comparisons

### Bash

- **profile**: benchmark bash functions

## Development

Developing pkgcraft-bash assumes that recent versions of rust, cargo, meson,
and bash are installed along with a standard C compiler.

Note that bash must be built with plugin support enabled and also have the
development files (.pc and headers) available on the system.

To build pkgcraft-bash, run the following commands:

```bash
# install cargo-c
cargo install cargo-c

# clone repos
git clone https://github.com/pkgcraft/pkgcraft.git
git clone https://github.com/pkgcraft/pkgcraft-c.git
git clone https://github.com/pkgcraft/pkgcraft-bash.git

# build plugins
cd pkgcraft-bash
./scripts/build
```

## Usage

Plugin usage varies depending on what the plugin is meant for. See the
following example using the **profile** plugin to benchmark the **ver_test**
plugin vs its native implementation.

```bash
# load plugins
enable -f build/src/profile.so profile
enable -f build/src/ver_test.so ver_test

# profile ver_test plugin that uses pkgcraft
profile ver_test 1.2.3.4.5 -lt 1.2.3.4.5_p

# profile ver_test bash implementation
source benches/pkgcore.bash
profile ver_test 1.2.3.4.5 -lt 1.2.3.4.5_p
```

[1]: <https://projects.gentoo.org/pms/latest/pms.html>

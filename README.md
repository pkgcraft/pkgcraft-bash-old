# pkgcraft-bash

Various bash plugins that leverage pkgcraft's C API instead of being forced to
maintain duplicate functionality such as version parsing and comparisons in
bash. The canonical definition for many of the plugins comes from the [Package
Manager Specification][1] used by Gentoo.

## Plugins

- **has**: determine if a string is in a list of strings
- **ver_cut**: output version substrings
- **ver_rs**: perform version string substitutions
- **ver_test**: perform version comparisons

## Development

Developing pkgcraft-bash assumes that recent versions of rust, cargo, meson,
and bash are installed along with a standard C compiler.

Note that bash must be built with plugin support enabled and also have the
development files (.pc and headers) available on the system.

To build pkgcraft-bash, run the following commands:

    # install cargo-c
    cargo install cargo-c

    # clone repos
    git clone https://github.com/pkgcraft/pkgcraft.git
    git clone https://github.com/pkgcraft/pkgcraft-c.git
    git clone https://github.com/pkgcraft/pkgcraft-bash.git

    cd pkgcraft-bash

    # build and install pkgcraft-c
    cargo cinstall --prefix="${PWD}/pkgcraft" --pkgconfigdir="${PWD}/pkgcraft" --manifest-path=../pkgcraft-c/Cargo.toml

    # build pkgcraft-bash
    export PKG_CONFIG_PATH=pkgcraft
    meson setup build && meson compile -C build -v

    # bash plugin loading example
    bash -c "enable -f build/src/ver_test.so ver_test && ver_test 1 -lt 2"


[1]: <https://projects.gentoo.org/pms/latest/pms.html>

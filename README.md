# pkgcraft-bash

Various bash plugins that leverage pkgcraft's C API instead of being forced to
maintain duplicate functionality such as version parsing and comparisons in
bash.

## Plugins

- **[ver_cut][1]**: output version substrings
- **[ver_rs][1]**: perform version string substitutions
- **[ver_test][1]**: perform version comparisons

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

    # build pkgcraft-c
    cargo cinstall --prefix="${HOME}/.local" --manifest-path=../pkgcraft-c/Cargo.toml

    # build pkgcraft-bash
    export PKG_CONFIG_PATH="${HOME}/.local/lib/pkgconfig"
    meson setup build && meson compile -C build -v

    # bash plugin loading example
    bash -c "enable -f build/src/ver_test.so ver_test && ver_test 1 -lt 2"


[1]: <https://projects.gentoo.org/pms/latest/pms.html#x1-13400012.3.14>

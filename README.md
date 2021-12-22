# pkgcraft-bash

Various bash plugins that leverage pkgcraft's C API instead of being forced to
maintain duplicate functionality such as version parsing and comparisons in
bash.

## Plugins

- **[ver_cut][1]**: output version substrings
- **[ver_rs][1]**: perform version string substitutions
- **[ver_test][1]**: perform version comparisons

## Requirements

- **pkgcraft**: the C library and its related header file
- **bash**: plugins support must be enabled and development files should be available (.pc and headers)

[1]: <https://projects.gentoo.org/pms/latest/pms.html#x1-13400012.3.14>

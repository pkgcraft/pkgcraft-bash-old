project(
  'pkgcraft-bash', 'c',
  version : '0.0.1',
  license : 'GPL-3',
  meson_version : '>= 0.50.0',
)

bash_prog = find_program('bash')
bash = dependency('bash', version: '>= 5.0')
bash_loadablesdir = bash.get_pkgconfig_variable('loadablesdir')

pkgcraft = dependency('pkgcraft', version: '>= 0.0.1')

subdir('src')

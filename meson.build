project(
  'pkgcraft-bash', 'c',
  version : '0.0.1',
  license : 'GPL-3',
  meson_version : '>= 0.58.0',
)

incdir = include_directories('include')
bash = dependency('bash', version: '>= 5.0')
bash_loadablesdir = bash.get_variable(pkgconfig : 'loadablesdir')

pkgcraft = dependency('pkgcraft', version: '>= 0.0.1')

subdir('src')

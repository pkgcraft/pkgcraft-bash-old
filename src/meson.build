shared_module(
  'ver_test',
  'ver_test.c',
  dependencies : [bash, pkgcraft],
  name_prefix : '',
  install : true,
)

test(
  'load ver_test plugin',
  bash_prog, args : ['-c', 'enable -f ./src/ver_test.so ver_test && ver_test || exit 1'])

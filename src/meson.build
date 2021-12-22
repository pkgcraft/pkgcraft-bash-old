shared_module(
  'ver_test', 'ver_test.c',
  dependencies : [bash, pkgcraft], name_prefix : '', install : true,
)

shared_module(
  'ver_rs', 'ver_rs.c',
  dependencies : [bash, pkgcraft], name_prefix : '', install : true,
)

shared_module(
  'ver_cut', 'ver_cut.c',
  dependencies : [bash, pkgcraft], name_prefix : '', install : true,
)

bash = find_program('bash')

test(
  'load ver_test plugin',
  bash, args : ['-c', 'enable -f ./src/ver_test.so ver_test && ver_test 1 -lt 2 || exit 1'])

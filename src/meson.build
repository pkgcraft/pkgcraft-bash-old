plugins = ['has', 'ver_cut', 'ver_rs', 'ver_test']

foreach name : plugins
  shared_module(name, f'@name@.c', dependencies : [bash, pkgcraft], name_prefix : '', install : true)
endforeach

bash = find_program('bash')

test(
  'load ver_test plugin',
  bash, args : ['-c', 'enable -f ./src/ver_test.so ver_test && ver_test 1 -lt 2 || exit 1'])

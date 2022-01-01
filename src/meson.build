pkgcraft_plugins = ['ver_cut', 'ver_rs', 'ver_test']
foreach name : pkgcraft_plugins
  shared_module(
    name, f'@name@.c', name_prefix : '', install : true,
    dependencies : [bash, pkgcraft], include_directories : incdir)
endforeach

bash_plugins = ['profile']
foreach name : bash_plugins
  shared_module(
    name, f'@name@.c', 'utils.c', name_prefix : '', install : true,
    dependencies : [bash], include_directories : incdir)
endforeach

bash_plugins = ['profile']
foreach name : bash_plugins
  shared_module(
    name, f'@name@.c', 'utils.c', name_prefix : '', install : true,
    dependencies : [bash], include_directories : incdir)
endforeach

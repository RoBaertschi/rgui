project('rgui', 'c',
  version : '0.1',
  meson_version : '>=1.1',
  default_options : ['warning_level=3'])

subdir('include')
subdir('src')

if get_option('build_examples')
  subdir('examples')
endif

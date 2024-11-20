project(
  'rgui',
  'c',
  version: '0.1',
  meson_version: '>=1.1',
  default_options: ['warning_level=3', 'c_std=c99'],
)

subdir('include')
subdir('src')

if get_option('build_examples')
  subdir('examples')
endif

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name: 'librgui',
  libraries: rgui,
  version: meson.project_version(),
  filebase: 'rgui',
  subdirs: 'include',
  description: 'Simple, immediate mode, gui library.',
)

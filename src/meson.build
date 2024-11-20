rgui_srcs = ['rgui.c']

rgui_args = []

if get_option('default_library') == 'shared'
  rgui_args += '-DRGUI_BUILD_SHARED'
endif

rgui = library(
  'rgui',
  rgui_srcs,
  c_args: rgui_args,
  include_directories: [rgui_include_dir],
  install: true,
)
rgui_dep = declare_dependency(include_directories: [rgui_include_dir], link_with: [rgui])

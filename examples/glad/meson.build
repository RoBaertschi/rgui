glad_include_dir = include_directories('include')
glad_srcs = ['src/gl.c']
glad = library('glad', glad_srcs, include_directories : [glad_include_dir], install : false)
glad_dep = declare_dependency(include_directories: [glad_include_dir], link_with: [glad])

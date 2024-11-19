rgui_srcs = ['rgui.c']

rgui = library('rgui', rgui_srcs, include_directories : [rgui_include_dir], install : true)
rgui_dep = declare_dependency(include_directories: [rgui_include_dir], link_with: [rgui])

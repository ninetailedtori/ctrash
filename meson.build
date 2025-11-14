project(
    'ctrash', 'cpp', 'c',
    version : '0.0.1',
    license : 'GPL3',
    meson_version : '>= 0.59.0',
    default_options : [
        'cpp_std=c++20',
        'buildtype=release',
        'default_library=shared',
        'auto_features=auto',
        'optimization=3'
    ],
)

compiler = meson.get_compiler('cpp')

cpp_args = []
cpp_link_args = []

if get_option('libcxx')
    cpp_args += ['-stdlib=libc++']
    cpp_link_args += ['-stdlib=libc++', '-lc++abi']
endif

if compiler.has_link_argument('-lc++fs')
    cpp_link_args += ['-lc++fs']
elif compiler.has_link_argument('-lstdc++fs')
    cpp_link_args += ['-lstdc++fs']
endif

git = find_program('git', native : true, required : false)

if not git.found()
    add_project_arguments('-DVERSION="@0@"'.format(meson.project_version()), language : 'cpp')
else
    git_path = run_command(git, 'rev-parse', '--show-toplevel', check : false).stdout().strip()
    if meson.project_source_root() == git_path
        git_commit_hash = run_command(git, 'describe', '--always', '--tags', check : false).stdout().strip()
        git_branch = run_command(git, 'rev-parse', '--abbrev-ref', 'HEAD', check : false).stdout().strip()
        version = '"@0@ (branch \'@1@\')"'.format(git_commit_hash, git_branch)
        add_project_arguments('-DVERSION=@0@'.format(version), language : 'cpp')
    else
        add_project_arguments('-DVERSION="@0@"'.format(meson.project_version()), language : 'cpp')
    endif
endif

add_global_arguments(cpp_args, language : 'cpp')
add_global_link_arguments(cpp_link_args, language : 'cpp')

is_linux = host_machine.system() == 'linux'
is_dragonfly = host_machine.system() == 'dragonfly'
is_freebsd = host_machine.system() == 'freebsd'
is_netbsd = host_machine.system() == 'netbsd'
is_openbsd = host_machine.system() == 'openbsd'

prefix = get_option('prefix')
sysconfdir = get_option('sysconfdir')
conf_data = configuration_data()
conf_data.set('prefix', prefix)

add_project_arguments('-DSYSCONFDIR="@0@"'.format(prefix / sysconfdir), language : 'cpp')

systemd = dependency('systemd', required : false)

if systemd.found()
    user_units_dir = systemd.get_variable(pkgconfig : 'systemduserunitdir')

    #    configure_file(
    #        configuration : conf_data,
    #        input : './resources/waybar.service.in',
    #        output : '@BASENAME@',
    #        install_dir : user_units_dir
    #    )
endif

src_files = files(
    'src/trash.cpp',
    'src/ctrash.cpp'
)

man_files = files(
    # string list here with all doc files.
)

inc_dirs = ['include']

libtrash = library('libtrash.so', 'src/trash.cpp')

executable(
    'ctrash',
    [src_files],
    dependencies : [], # can place dependencies external here.
    include_directories : inc_dirs,
    link_with : libtrash.so,
    install : true
)

install_data(
    # to fill in here, files to install.
    #     'resources/config.jsonc',
    #    'resources/style.css',
    #    install_dir: sysconfdir / 'xdg/waybar'
)

scdoc = dependency('scdoc', version : '>=1.9.2', native : true, required : get_option('man-pages'))

#if scdoc.found()
#    man_files += configure_file(
#        input : 'man/ctrash.5.scd.in',
#        output : 'ctrash.5.scd',
#        configuration : {
#            'sysconfdir' : prefix / sysconfdir
#        }
#    )
#
#    fs = import('fs')
#    mandir = get_option('mandir')
#    foreach file : man_files
#        basename = fs.name(file)
#
#        topic = basename.split('.')[-3]
#        section = basename.split('.')[-2]
#        output = '@0@.@1@'.format(topic, section)
#
#        custom_target(
#            output,
#            input : file,
#            output : output,
#            command : scdoc.get_variable('scdoc'),
#            feed : true,
#            capture : true,
#            install : true,
#            install_dir : '@0@/man@1@'.format(mandir, section)
#        )
#    endforeach
#endif

catch2 = dependency(
    'catch2',
    default_options : ['tests=false'],
    fallback : ['catch2', 'catch2_dep'],
    required : get_option('tests'),
)
if catch2.found()
    #    subdir('test')
endif

clangtidy = find_program('clang-tidy', required : false)

if clangtidy.found()
    run_target(
        'tidy',
        command : [
            clangtidy,
            '-checks=*,-fuchsia-default-arguments',
            '-p', meson.project_build_root()
        ] + src_files)
endif
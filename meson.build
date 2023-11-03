project('MicroHTTPKit', 'objc', version : '0.2.0', default_options : ['warning_level=3'])

# Ensure clang is used for Objective-C
objc_compiler = meson.get_compiler('objc')
if objc_compiler.get_id() != 'clang'
  error('Clang is required for this project. Please set CC=clang, and OBJC=clang before running Meson.')
endif
 
dependencies_to_link = []
# Common Objective-C flags
objc_flags = []

if host_machine.system() != 'darwin'
    # Objective-C (GNUstep) support from gnustep-config
    gnustep_config = find_program('gnustep-config', required: true)
    if not gnustep_config.found()
        error('GNUstep is required for this project. Please install GNUstep and ensure gnustep-config is in your PATH. You might want to source GNUstep.sh before running Meson.')
    endif

    gnustep_flags = run_command(gnustep_config, '--objc-flags', check: true).stdout().strip().split()
    gnustep_base_libs = run_command(gnustep_config, '--base-libs', check: true).stdout().strip().split()

    # Filter out flags that are handled by Meson's built-in options
    # or result in warnings (-MMD)
    foreach flag : gnustep_flags
    if flag != '-Wall' and flag != '-g' and flag != '-O2' and flag != '-MMD'
        objc_flags += flag
    endif
    endforeach

    add_project_link_arguments(gnustep_base_libs, language: 'objc')
else
  # Properly link against the Foundation framework
  foundation_dep = dependency('appleframeworks', modules: ['Foundation'])
  dependencies_to_link += foundation_dep

  add_project_link_arguments('-lobjc', language: 'objc')
endif

# Enable ARC (Automatic Reference Counting)
objc_flags += '-fobjc-arc'

# Add Objective-C flags
add_project_arguments(objc_flags, language: 'objc')

# Add libmicrohttpd dependency
libmicrohttpd_dep = dependency('libmicrohttpd', required: true)
dependencies_to_link += libmicrohttpd_dep

# Add libdispatch dependency when on Linux
if host_machine.system() != 'darwin'
  libdispatch_dep = dependency('libdispatch', required: true)
  dependencies_to_link += libdispatch_dep
endif

source = [
    # Objc files
    'src/HKHTTPServer.m',
    'src/HKRouter.m',
    'src/HKHTTPRequest.m',
    'src/HKHTTPRequest+Private.m',
    'src/HKHTTPResponse.m',
    'src/HKHTTPConstants.m',
]

include_dirs = include_directories(
    'MicroHTTPKit',
)

# Build MicroHTTPKit
microhttpkit_lib = library(
  'microhttpkit',
  source,
  dependencies: dependencies_to_link,
  include_directories: include_dirs,
  install: true,
)

subdir('tests')
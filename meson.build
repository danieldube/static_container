project('static_conrainer', 'cpp', default_options : ['cpp_std=c++14'])

static_vector = library('static_vector', 'include/static_vector.h')

subproject('catch2')
catch2_dep = dependency('catch2')
tests = executable('tests',
  'tests/static_vector_test.cpp', 'tests/instance_counter.h', 'tests/instance_counter_test.cpp',
  include_directories: include_directories('tests'),
  link_with: [static_vector],
  dependencies: [catch2_dep])
test('unit tests', tests)

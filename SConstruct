# -*- coding:utf-8 -*-
DEBUG = True

env = Environment(COMPILATIONDB_USE_ABSPATH=True)
env.Tool('compilation_db')
env.CompilationDatabase()   

if DEBUG:
    env.Append(CPPFLAGS=['-g', '-O0', '-Wall', '-W'])
else:
    env.Append(CPPFLAGS=['-O3'])
env.Export("env")

env.VariantDir('#/build/src', '#/src', duplicate=0)
env.SConscript('#/build/src/SConscript')

env.VariantDir('#/build/test', '#/test', duplicate=0)
env.SConscript('#/build/test/SConscript')

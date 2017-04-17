TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    src/restqtful.pro \
    example \
    tests
example.depends = src
tests.depends = src


#!/bin/bash

# define NT2_SOURCE_ROOT
old_path=`pwd`
cd ../..
export NT2_SOURCE_ROOT=`pwd`
cd "$old_path"

# Find all modules in current directory
directories=`find . -name CMakeLists.txt | sed s/CMakeLists.txt$//g`

for i in $directories
do
    if echo "$directories" | grep $i > /dev/null
    then
      directories=`echo "$directories" | grep -v $i`
      directories=`echo -ne "$directories\n$i"`
    fi
done

# Transform paths to modules
directories=`echo "$directories" | sed -r 's@^./(.*)/$@\1@g'`
modules=`echo "$directories" | sed -r 's@^@boost/@g' | sed  's@/@.@g'`

# $1 path to install dir, $2+ list of modules
function build_modules
{
    echo "Building modules ${@:2}"
    modules=`echo ${@:2} | sed 's/ /;/g'`
    mkdir "/tmp/_nt2_build"
    old_path=`pwd`
    cd "$1"
    install_prefix=`pwd`
    cd "/tmp/_nt2_build"
    cmake "$NT2_SOURCE_ROOT" "-DCMAKE_INSTALL_PREFIX=$install_prefix" "-DNT2_MODULES=$modules"
    make -j8 && make -j8 postconfigure
    make install
    cd "$old_path"
    rm -rf "/tmp/_nt2_build"
}

rm -rf boostification_build
mkdir -p boostification
cp -r boostification boostification_build

mkdir boostification_tmp
build_modules boostification_tmp $modules

# copy all boost simd includes
cp -r boostification_tmp/include/boost boostification_build

# copy mini_nt2 into Boost.SIMD
cwd=`pwd`
cd boostification_tmp/include
for j in `find nt2 -name '*.hpp'`
do
    mkdir -p "$cwd/boostification_build/libs/simd/mini_nt2"
    cp --parents "$j" "$cwd/boostification_build/libs/simd/mini_nt2"
done
cd "$cwd"

# copy sources and unit tests
for i in `echo "$directories"`
do
    top=`echo $i | sed -r 's@^([^/]+)/.*$@\1@g'`
    
    # copy sources
    cd $i/src
    for j in `find . -name '*.cpp'`
    do
        mkdir -p "$cwd/boostification_build/libs/$top/src"
        cp --parents "$j" "$cwd/boostification_build/libs/$top/src"
    done;
    cd $cwd
    
    # copy tests
    cd $i/unit
    for j in `find . -name '*.cpp'`
    do
        mkdir -p "$cwd/boostification_build/libs/$top/test"
        cp --parents "$j" "$cwd/boostification_build/libs/$top/test"
    done;
    cd $cwd
    
done

rm -rf boostification_tmp

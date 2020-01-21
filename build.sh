BUILD_DIR=build

platform='unknown'
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
    platform='linux'
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='macosx'
fi

OUT_PACKAGES=generated_packages
if [[ ! -d $OUT_PACKAGES ]]; then
    mkdir $OUT_PACKAGES
fi

if [[ $platform == 'linux' ]]; then

    DEFAULT_LANG=pt fakeroot dpkg-buildpackage -j3 -b -us -uc
    DEFAULT_LANG=sp fakeroot dpkg-buildpackage -j3 -b -us -uc
    DEFAULT_LANG=en fakeroot dpkg-buildpackage -j3 -b -us -uc

    mv ../muan-*.deb $OUT_PACKAGES
    rm -f ../muan_*.changes

    ./debian/rules clean
    MUAN_VERSION=$(grep  -ow '[[:digit:]][[:digit:]]\.[[:digit:]]\.[[:digit:]]' CMakeLists.txt)
    cd ..
    echo "Creating Source Package..."
    tar --exclude=build --exclude=.git* --exclude=$OUT_PACKAGES -czf muan_src-$MUAN_VERSION.tar.gz muan-star
    cd -
    mv ../muan_src-$MUAN_VERSION.tar.gz $OUT_PACKAGES


elif [[ $platform == 'macosx' ]]; then

    if [ ! -d $BUILD_DIR ]; then
            mkdir $BUILD_DIR
    fi
    cd $BUILD_DIR

    echo "**** Building Portuguese version ****"
    rm -rf *
    cmake -DDEFAULT_LANG=pt .. && make -j3 package
    mv *.dmg ../$OUT_PACKAGES

    echo "**** Building Portuguese Spanish ****"
    rm -rf *
    cmake -DDEFAULT_LANG=sp .. && make -j3 package
    mv *.dmg ../$OUT_PACKAGES

    echo "**** Building English version ****"
    rm -rf *
    cmake -DDEFAULT_LANG=en .. && make -j3 package
    mv *.dmg ../$OUT_PACKAGES

    cd .. 

fi


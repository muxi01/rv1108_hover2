#! /bin/bash

TOP_DIR=$(pwd)
OUT_PATH=./out
COMMON_PATH=./common
COMMON_SYSTEM_PATH=$COMMON_PATH/system
COMMON_ROOT_PATH=$COMMON_PATH/root
CLEAN_CMD=cleanthen

#remove out path
[ -d $OUT_PATH ] && rm -rf $OUT_PATH
mkdir -p $OUT_PATH
cp -R $COMMON_SYSTEM_PATH $OUT_PATH
cp -R $COMMON_ROOT_PATH $OUT_PATH

logfile="/dev/null"
check_cmd(){
    "$@" >> $logfile 2>&1
}
check_cc(){
  check_cmd arm-linux-gcc -v
}
check_cc
if [ $? -eq 127 ];then
        export PATH=$PATH:$TOP_DIR/prebuilts/toolschain/usr/bin
fi
shopt -s expand_aliases
alias arm-linux-gcc='arm-linux-gcc -s -O2'
#alias arm-linux-gcc='arm-linux-gcc -g -rdynamic -O2'

# call cmake first
export CVR_SDK_ROOT="$(pwd)"
CMAKE_VERSION=$(cmake --version 2>/dev/null | grep "cmake version")
if [ "$CMAKE_VERSION" = "" ];then
echo "Error: cannot find cmake."
echo "You should install cmake at first as follows:"
echo "sudo apt-get install cmake"
exit
fi
rm -rf out_cmake && mkdir out_cmake 2>/dev/null
cd out_cmake
cmake -DCMAKE_TOOLCHAIN_FILE=$CVR_SDK_ROOT/build/toolchain-arm-linux.cmake \
      -DCMAKE_INSTALL_PREFIX=$CVR_SDK_ROOT/out/system ..
make -j4 && make install
cd ..

FILE='.cvrmkdirs_first'
find $TOP_DIR -name cvr_make_first.sh | sort -r > $FILE
while read line;do
        #echo "Line # $k: $line"
        mk_path=$(echo $line | sed -r 's@^(/.*/)[^/]+/?@\1@g')
        cd $mk_path
        source $mk_path/cvr_make_first.sh $1 $CLEAN_CMD
        cd $TOP_DIR
        #echo $mk_path
        #echo $(pwd)
done < $FILE
rm .cvrmkdirs_first

FILE='.cvrmkdirs'
find $TOP_DIR -name cvr_make.sh | sort -r > $FILE
while read line;do
        #echo "Line # $k: $line"
	mk_path=$(echo $line | sed -r 's@^(/.*/)[^/]+/?@\1@g')
        cd $mk_path
	source $mk_path/cvr_make.sh $1 $CLEAN_CMD
	cd $TOP_DIR
	#echo $mk_path
	#echo $(pwd)
done < $FILE
rm .cvrmkdirs


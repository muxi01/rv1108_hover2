#! /bin/bash
#
# Before build your RK1108 SDK, you must execute "source config/envsetup.sh" at
# SDK root to setup the build environment first.
#
# Adding your own useful commands and enviornment variables here is very welcome.
#
# If you have any question about build system of RK1108, please send a email to
# huaping.liao@rock-chips.com for help.
#

# Setup toolchain
version=$(arm-linux-gcc --version 2>/dev/null)
result=$(echo $version | grep -Eo '*Buildroot 2016.05-rc2*')
if [ ! "$version" = "" ] && [ "$result" = "" ] ;then
	export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$(pwd)/prebuilts/toolschain/usr/bin:$PATH"
	export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$(pwd)/prebuilts/toolschain/usr/arm-rkcvr-linux-uclibcgnueabihf/bin:$PATH"
	echo "Another gcc found, will be replaced by RK1108 SDK toolchain"
elif [ "$version" = "" ] ;then
	export PATH="$PATH:$(pwd)/prebuilts/toolschain/usr/bin"
	export PATH="$PATH:$(pwd)/prebuilts/toolschain/usr/arm-rkcvr-linux-uclibcgnueabihf/bin"

	version=$(arm-linux-gcc --version)
	echo "Set toolchain path to: <SdkRoot>/prebuilts/toolschain"
#	echo $version
fi

# Export rk1108 sdk root directory
export CVR_SDK_ROOT="$(pwd)"

# Set croot alias
alias croot="cd $(pwd)"

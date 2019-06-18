
BUILT_TARGET="Debug"

if [ "$#" == 0 ]; then
	BUILD_TARGET="Debug"
else
	BUILD_TARGET="$1"
fi

export CURRENT_DIR=$(pwd)
export VULKAN_SDK=$CURRENT_DIR/vulkansdk/macOS
export VK_LAYER_PATH=$VULKAN_SDK/etc/vulkan/explicit_layer.d/
export VK_ICD_FILENAMES=$VULKAN_SDK/etc/vulkan/icd.d/MoltenVK_icd.json/

rm -rf buildux
mkdir buildux
cd buildux
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" "${@:1}" ../
make -j 4

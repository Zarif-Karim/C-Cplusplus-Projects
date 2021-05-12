#!/bin/bash

_ins_files=installation_files
_ws_dir=sudoku_bot_ws

echo "Install DIR: $_ws_dir"

mkdir -p $_ws_dir/src
cd $_ws_dir

echo "\nCREATED WORKSPACE DIRECTORY STRUCTURE\n\n"

# first build without packages
catkin_make
echo "---- FIRST BUILD DONE ----"

cd ..

# copy packages to src folder of workspace
# and build again
cp -r $_ins_files/packages/* $_ws_dir/src
cd $_ws_dir
echo "---- PACKAGES COPIED ----"

# second build with packages (no cpp)
catkin_make
echo "---- SECOND BUILD DONE ----"

# copy header files to devel/include of workspace
cd ..
cp $_ins_files/headers/* $_ws_dir/devel/include
echo "---- HEADERS COPIED ----"

# copy new CMakeLists.txt for each package
cp $_ins_files/pkg_cmake_secondbuild/interface/CMakeLists.txt $_ws_dir/src/interface
cp $_ins_files/pkg_cmake_secondbuild/move_arm_joints/CMakeLists.txt $_ws_dir/src/move_arm_joints
cp $_ins_files/pkg_cmake_secondbuild/mover_client/CMakeLists.txt $_ws_dir/src/mover_client
cp $_ins_files/pkg_cmake_secondbuild/sudoku_pub/CMakeLists.txt $_ws_dir/src/sudoku_pub
echo "---- CMakeLists.txt COPIED ----"

# last build with cpp to generate executables
cd $_ws_dir
catkin_make
echo "---- THIRD BUILD DONE ----"

cd ..

# copy executables and other files
cp $_ins_files/executables/* $_ws_dir/devel/lib/move_arm_joints
cp $_ins_files/ws_files/* $_ws_dir
echo "---- COPYING EXTERNAL FILES DONE ----"
echo ""
echo "---- INSTALLATION FINISHED ----"
echo "GO TO WORKSPACE DIRECTORY AND EXECUTE FOLLOWING COMMAND TO RUN:"
echo "...$ ./run.sh"
echo "(--NEED TO HAVE 'roscore' RUNNING ON A SEPARATE TERMINAL--)"
echo ""
echo "AFTER USE EXECUTE FOLLOWING COMMAND TO CLEAN UP"
echo "BACKGROUND PROCESSES:"
echo "...$ ./terminate.sh"
echo ""
echo ""



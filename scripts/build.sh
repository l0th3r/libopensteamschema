#!/bin/bash
set -e

BUILD_TYPE=Debug
BUILD_DIR=.build
CMAKE_FLAGS=()

# Doc
# DOC_REQUESTED=false

# Test and coverage
TEST_REQUESTED=false
# COVR_REQUESTED=false
# COVR_EXE_REQUESTED=false

for arg in "$@";
  do
    if [ "$arg" == "-test" ]; then
      CMAKE_FLAGS+=("-DOPENITEMDEF_BUILD_TESTS=ON")
      TEST_REQUESTED=true
    elif [ "$arg" == "-btest" ]; then
      CMAKE_FLAGS+=("-DOPENITEMDEF_BUILD_TESTS=ON")
    elif [ "$arg" == "-release" ]; then
      BUILD_TYPE=Release
    fi
done

echo ">> Building lib"

cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE "${CMAKE_FLAGS[@]}"
cmake --build "$BUILD_DIR" --config $BUILD_TYPE

if [ "$TEST_REQUESTED" = true ]; then
  echo
  echo ">> Testing lib"
  ctest --test-dir "$BUILD_DIR" --output-on-failure
fi
#!/bin/bash
set -e

BUILD_TYPE=Release
BUILD_DIR=build
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
      CMAKE_FLAGS+=("-DLIBOPENSTEAMSCHEMA_BUILD_TESTS=ON")
      TEST_REQUESTED=true
    elif [ "$arg" == "-btest" ]; then
      CMAKE_FLAGS+=("-DLIBOPENSTEAMSCHEMA_BUILD_TESTS=ON")
    # elif [ "$arg" == "-covr" ]; then
    #   COVR_REQUESTED=true
    #   COVR_EXE_REQUESTED=true
    # elif [ "$arg" == "coverage" ]; then
    #   COVR_REQUESTED=true
    # elif [ "$arg" == "docs" ]; then
    #   MODULES+=("$arg")
    #   DOC_REQUESTED=true
    fi
done

echo ">> Building lib"

# if [ "$COVR_REQUESTED" = true ]; then
#   CMAKE_FLAGS+=("-DLIBOPENSTEAMSCHEMA_ENABLE_COVERAGE=ON")
#   BUILD_TYPE=Debug
# fi

cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE "${CMAKE_FLAGS[@]}"
cmake --build "$BUILD_DIR" --config $BUILD_TYPE

#   if [ "$DOC_REQUESTED" = true ]; then
#     echo ">> Generating documentation with Doxygen..."
#     cmake -B "$BUILD_DIR"
#     cmake --build "$BUILD_DIR" --target docs
#   fi

if [ "$TEST_REQUESTED" = true ]; then
  echo
  echo ">> Testing lib"
  ctest --test-dir "$BUILD_DIR" --output-on-failure
fi

#   if [ "$COVR_EXE_REQUESTED" = true ]; then
#     echo ">> Capturing coverage..."
#     lcov --directory "$BUILD_DIR" --capture --output-file "$BUILD_DIR/coverage.info"
#     lcov --remove "$BUILD_DIR/coverage.info" '/usr/*' '*/tests/*' -o "$BUILD_DIR/coverage.cleaned.info"
#     genhtml "$BUILD_DIR/coverage.cleaned.info" --output-directory "$BUILD_DIR/coverage-report" --legend --title "libopenmodelviewer Coverage"
#     echo ">> Coverage report available in: $BUILD_DIR/coverage-report/index.html"
#   fi
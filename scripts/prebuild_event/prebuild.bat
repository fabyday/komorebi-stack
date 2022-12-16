echo "=====prebuild-start======"
cmake -S"%SolutionDir%3rd_party\jsoncpp" -B"%SolutionDir%3rd_party\jsoncpp\build" -A x64 -DCMAKE_BUILD_TYPE=%Configuration% -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=%SolutionDir%/libs -DCMAKE_MAKE_PROGRAM:PATH="%DevEnvDir%\devenv.exe"
echo "=====prebuild-end======"
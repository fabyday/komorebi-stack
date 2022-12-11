@REM SET DevEnvDir=$(DevEnvDir)
@REM SET SolutionDir=$(SolutionDir)
@REM SET Configuration=$(Configuration)
echo "link-build-start======"
cmake --build "%SolutionDir%3rd_party\jsoncpp\build" --target "jsoncpp_static" --config %Configuration%
IF NOT EXIST "%SolutionDir%lib\%Configuration%\" MKDIR "%SolutionDir%lib\%Configuration%\"
COPY %SolutionDir%3rd_party\jsoncpp\build\lib\%Configuration%\jsoncpp.lib %SolutionDir%lib\%Configuration%
echo "link-build-end======"

set PROGRAM="%~1"

rem Rugular test
%PROGRAM% 10 > %TEMP%\output.txt
fc %TEMP%\output.txt ten.txt
if ERRORLEVEL 1 goto err

rem test < 2
%PROGRAM% 1 > %TEMP%\output.txt
fc %TEMP%\output.txt 1.txt
if ERRORLEVEL 1 goto err

rem test over Diaposon
%PROGRAM% 100000001111 > %TEMP%\overDiaposonTest.txt
fc %TEMP%\overDiaposonTest.txt overDiaposon.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0
:err
echo Program testing failed
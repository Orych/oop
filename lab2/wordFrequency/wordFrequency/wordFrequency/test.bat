
set PROGRAM="%~1"

rem Regular 
%PROGRAM% input01.txt > %TEMP%\output01.txt
fc word01.txt %TEMP%\output01.txt
if ERRORLEVEL 1 goto err

rem Regular with empty
%PROGRAM% input02.txt > %TEMP%\output02.txt
fc word02.txt %TEMP%\output02.txt
if ERRORLEVEL 1 goto err

rem Regular with big
%PROGRAM% input03.txt > %TEMP%\output03.txt
fc word03.txt %TEMP%\output03.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
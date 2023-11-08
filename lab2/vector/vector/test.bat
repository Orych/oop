set PROGRAM="%~1"

rem input without numbers
%PROGRAM% input01.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output01.txt
if ERRORLEVEL 1 goto err

rem input with double numbers
%PROGRAM% input02.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output02.txt
if ERRORLEVEL 1 goto err

rem input with double numbers and < 0
%PROGRAM% input03.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output03.txt
if ERRORLEVEL 1 goto err

rem input with int numbers 
%PROGRAM% input04.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output04.txt
if ERRORLEVEL 1 goto err

rem input with int numbers and < 0
%PROGRAM% input05.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output05.txt
if ERRORLEVEL 1 goto err

rem input with int and double numbers
%PROGRAM% input06.txt > %TEMP%\output.txt
fc %TEMP%\output.txt output06.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0
:err
echo Program testing failed
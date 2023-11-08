
set PROGRAM="%~1"

rem Regular inversion
%PROGRAM% matrix01.txt > %TEMP%\invert01.txt
fc invert01.txt %TEMP%\invert01.txt
if ERRORLEVEL 1 goto err

rem Inversion with double numbers
%PROGRAM% matrix02.txt > %TEMP%\invert02.txt
fc invert02.txt %TEMP%\invert02.txt
if ERRORLEVEL 1 goto err

rem Inversion with singular matrix
%PROGRAM% matrix03.txt > %TEMP%\invert03.txt
fc invert03.txt %TEMP%\invert03.txt
if ERRORLEVEL 1 goto err

rem Inversion without number in matrix
%PROGRAM% matrix04.txt > %TEMP%\invert04.txt
fc invert04.txt %TEMP%\invert04.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
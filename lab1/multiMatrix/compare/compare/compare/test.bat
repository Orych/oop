
set PROGRAM="%~1"

%PROGRAM% one-line-Hello.txt one-line-Hello.txt > %TEMP%\output.txt
fc equal.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

%PROGRAM% multi-line-Hello.txt multi-line-Hello.txt > %TEMP%\output.txt
fc equal.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

%PROGRAM% one-line-Hello.txt multi-line-Hello.txt > %TEMP%\output.txt
fc error-line-2.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

%PROGRAM% one-line-Hello.txt one-line-Buy.txt > %TEMP%\output.txt
fc error-line-1.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

%PROGRAM% multi-line-Hello.txt multi-line-Buy.txt > %TEMP%\output.txt
fc error-line-1.txt  %TEMP%\output.txt
if ERRORLEVEL 1 goto err



echo Program testing succeeded
exit 0

:err
echo Program testing failed
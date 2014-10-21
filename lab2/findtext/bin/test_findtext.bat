REM запуск программы без параметров
findtext.exe
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
findtext.exe "pascalFile.txt"
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустой строкой в качестве одного из параметров
findtext.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с двумя параметрами (и проверяем результат)
findtext.exe "pascalFile.txt" BEGIN
IF ERRORLEVEL 1 GOTO err
FC /B output.txt BEGIN.txt
IF ERRORLEVEL 1 GOTO err

REM запуск программы с двумя параметрами (искомой строки заведомо нет в файле)
findtext.exe "pascalFile.txt" begin
IF NOT ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT

REM ������ ��������� ��� ����������
solve.exe
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ���������� ����������
solve.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ������ ������� � �������� ������ �� ����������
solve.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ����� ��������� �����������
solve.exe 1 2
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� ����������� � ������ �������
solve.exe 0 2 1
IF NOT ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� �����������
solve.exe 1 2 1 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 111.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� �����������
solve.exe 2 5 3 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 253.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��������� � ����� ��������� �����������
solve.exe 2 2 1 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 221.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT

@echo off
echo File Branch_Vertices Time Verification Branch_Vertices2 Time2 Verification2 > resultado.txt
for /f %%f in ('dir /b Instancias\Spd_*.txt') do (	
	bin\Release\ArvoreGeradora.exe Instancias\%%f >> resultado.txt
)
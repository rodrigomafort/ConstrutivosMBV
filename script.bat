@echo off
echo File Branch_Vertices Time Verification > resultado.txt
for /f %%f in ('dir /b Instancias\Spd_*.txt') do (	
	ArvoreGeradora.exe Instancias\%%f >> resultado.txt
)
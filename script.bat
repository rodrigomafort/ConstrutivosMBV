@echo off
echo File Branch_Vertices Time Verification M�dia_Grau_BV Branch_Vertices2 Time2 Verification2 M�dia_Grau_BV2 Branch_Vertices3 Time3 Verification3 M�dia_Grau_BV3 > resultado.txt
for /f %%f in ('dir /b Instancias\Spd_*.txt') do (	
	bin\Release\ArvoreGeradora.exe Instancias\%%f >> resultado.txt
)
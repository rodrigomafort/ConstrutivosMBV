@echo off
echo File Branch_Vertices Time Verification M�dia_Grau_BV Branch_Vertices2 Time2 Verification2 M�dia_Grau_BV2 Branch_Vertices3 Time3 Verification3 M�dia_Grau_BV3 > resultado2.txt
for /f %%f in ('dir /b Instancias2\Grafo_*.txt') do (	
	bin\Release\ArvoreGeradora.exe Instancias2\%%f >> resultado2.txt
)
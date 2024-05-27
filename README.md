# Kalkulator-ONP
Napisz kalkulator liczb całkowitych. Użyj notacji postfiksowej do obsługi kolejności wykonywania operacji, funkcji i nawiasów.
Wejście:
n -liczba formuł
n formuł, każda w formie podanej poniżej.
Każda formuła jest prawidłowym wyrażeniem w notacji infiksowej z funkcjami i kończy się kropką ('.'). Każdy token jest oddzielony kilkoma białymi znakami. Każdy operand jest dodatnią liczbą całkowitą (chociaż wynik operacji może być ujemny). Każdy operator to pojedynczy znak, a każda nazwa funkcji składa się wyłącznie z wielkich liter.
Dostępne są następujące operacje, w kolejności rosnącego priorytetu:

a + b, a - b;
a * b, a / b -wszystkie operacje wykonywane są na liczbach całkowitych, stąd wynik dzielenia zaokrąglany jest w dół (standardowy operator '/' w C). Nie można dzielić przez 0 (zobacz przykładowe dane wyjściowe);
IF(a, b, c) -jeśli a> 0 zwróć b, w przeciwnym razie c,
N a -jednoargumentowa negacja, czyli -a,
MIN( a1, a2, ... ) , MAX(a1, a2, ...) -funkcje MIN i MAX nie mają ograniczonej liczby parametrów;
( ... ) -nawiasy.
Wyjście dla każdej formuły:
formuła w notacji postfiksowej ;
przed wykonaniem każdej operacji wypisz operator lub funkcję i zawartość stosu;
wynik końcowy;
jeśli napotkasz dzielenie przez 0, wypisz „ERROR” i przejdź do następnego wyrażenia.

# mlita_coloc


3 Задание.
Правила поиска противоречий в наборе:
1. Объединение импликаций: если есть несколько импликаций их можно "объединять". Например из A => B, B => C можно получить A => C. Это объясняется транзитивностью импликации.
2. Отрицание: при резольвировании двух посылок вида Q => R и NOT R, получается резольвента NOT Q. Это объясняется тем, что при ложном втором члене иммплакции она истинна, только в случае ложности первого.

Пример работы:
R1 = A => B
R2 = B => C
R3 = A
R4 = NOT C

R5 = R1 r R2 = A => C
R6 = R2 r R4 = NOT B
R7 = R5 r R4 = NOT A
R8  = R1 r R6 = NOT A

Так как в наборе пристуствуют A и NOT A набор противоречив.

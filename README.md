# Коллоквиум по МЛиТА: Выводимость логических формул из аксиом

## Постановка задачи

Известны аксиомы исчисления высказываний:

A1.   (A→(B→A))

A2.   ((A→(B→C))→((A→B)→(A→C)))

A3.   ((-B→-A)→((-B→A)→B))

Из этих аксиом и правила вывода Modus ponens можно вывести все тождественные формулы исчисления высказываний, например, закон Моргана и пр.

Modus ponens:   A, A→B ⊢ B

Конъюнкция и дизъюнкция выражаются через отрицание и импликацию.

## Задание 1

Нужно написать программу, которая выведет все следующие тождества (которые часто рассматриваются как аксиомы).  При ускорения вывода полезно использовать теорему о дедукции ( Аксиомы и правила вывода теорема 7 на стр. 5).

A4:   A∧B→A

A5:   A∧B→B

A6:   A→(B→(A∧B))

A7:   A→(A∨B)

A8:   B→(A∨B)

A9:   (A→C)→((B→C)→((A∨B)→C))

A10:   ¬A→(A→B)

A11:   A∨¬A

## Выполнение 1 задания

Для решения задания №1 была написана система классов, позволяющая работать с логическими выражениями:

1. Класс SyntaxTree (синтаксическое дерево):
* Структура для представления формулы в виде синтаксического дерева.
* Метод printTree() — вывод дерева в консоль для наглядности.
* Метод toString() — преобразует дерево обратно в строковое представление формулы.

2. Класс FormulaParser (парсер формулы):
* Отвечает за разбор строковых выражений в виде дерева (SyntaxTree).
* Допустимые логические операции: Отрицание — `!`, Импликация — `>`, Дизъюнкция — `|`, Конъюнкция — `*`.
* Метод Parse() — принимает строку формулы и возвращает дерево узлов.

3. Класс Axioms (аксиомы):
* Хранит определения аксиом A1–A11.
* Методы A1(), A2(), ..., A11() создают соответствующие аксиомы через парсер формул и возвращают их.
* Метод GetAxioms1To3() — возвращает аксиомы A1–A3.
* Метод GetAxioms4To11() — возвращает аксиомы A4–A11.

4. Класс ModusPonens:
* Реализует правило Modus Ponens: из двух формул A и A → B позволяет вывести B.
* Метод Apply() — проверяет применимость правила и возвращает результат.

5. Класс Substitution (подстановка):
* Обеспечивает подстановку значений переменных в выражения.
* Метод Apply() — применяет подстановку для дерева выражения.

6. Класс TheoremProver (доказательство теоремы):
* Позволяет доказывать тождества, используя базовые аксиомы логики и правило Modus Ponens.
* Метод Prove() — пытается доказать целевое тождество.

Также были написаны тесты, тестирующие парсер строковых выражений, подстановку выражений в выражения, правило Modus Ponens.

К сожалению, нам не удалось вывести правило, по которому выбирать такую подстановку для замены выражения на другое выражение, чтобы итоговые тождества не росли в объёме, а сокращались за счёт применения Modus Ponens.

## Задание 3
Правила поиска противоречий в наборе:

Правила резолюций:
1. Объединение импликаций: если есть несколько импликаций их можно "объединять". Например из A => B, B => C можно получить A => C. Это объясняется транзитивностью импликации.
2. Отрицание: при резольвировании двух посылок вида Q => R и NOT R, получается резольвента NOT Q. Это объясняется тем, что при ложном втором члене иммплакции она истинна, только в случае ложности первого.

Эквивалентные записи:  
1. Перестановка: P => Q можно представить в виде NOT Q => NOT P. Это объясняется тем, что NOT P OR Q = Q OR NOT P.
2. P => NOT P можно представить в виде NOT P. NOT P =>  P можно представить в виде P. 

Пример работы:

R1 = A => B

R2 = B => C

R3 = A

R4 = NOT C

R5 = NOT B => NOT A

R6 = NOT C => NOT B

R7 = R1 r R2 = A => C

R8 = R2 r R4 = NOT B

R9 = R7 r R4 = NOT A

R10  = R1 r R8 = NOT A

Так как в наборе пристуствуют A и NOT A набор противоречив.

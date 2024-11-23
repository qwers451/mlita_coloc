class LogicalResolution:
    def __init__(self):
        self.statements = []

    def add_statement(self, statement):
        self.statements.append(statement)

    def resolve(self):
        # Храним все возможные резольвенты
        resolved = set(self.statements)
        new_resolved = set()

        while True:
            # Счетчик для проверки появления новых резольвентов
            resolved_length = len(resolved)

            for i in range(len(self.statements)):
                for j in range(len(self.statements)):
                    if i != j:
                        resolvent = self.resolution_step(self.statements[i], self.statements[j])
                        if resolvent:
                            self.add_statement(resolvent)
                            new_resolved.add(resolvent)


            # Добавление новых резольвентов в общее множество
            resolved = resolved.union(new_resolved)
            print(resolved)

            # Проверяем, не найдено ли противоречие
            if "NOT A" in resolved and "A" in resolved:
                print("Противоречие найдено: набор утверждений противоречив.")
                return True
            elif "NOT B" in resolved and "B" in resolved:
                print("Противоречие найдено: набор утверждений противоречив.")
                return True
            elif "NOT C" in resolved and "C" in resolved:
                print("Противоречие найдено: набор утверждений противоречив.")
                return True

            # Если не появилось новых резольвентов, выходим из цикла
            if len(resolved) == resolved_length:
                break

            # Очищаем новое множество резольвентов для следующей итерации
            new_resolved.clear()

        print("Противоречия не обнаружено.")
        return False

    def resolution_step(self, statement1, statement2):
        #print(statement1,"|", statement2, "stat")
        # Разделяем утверждения по стрелке и убираем лишние пробелы
        if "=>" in statement1 and "=>" in statement2:
            A, B = statement1.split(" => ")
            C, D = statement2.split(" => ")
            if B == C:
                return f"{A} => {D}"
        if "=>" in statement1 and "=>" not in statement2:
            A, B = statement1.split(" => ")
            C = statement2[-1]
            if C == B[-1]:
                if "NOT" in statement2:
                    if "NOT" not in B:
                        if "NOT" not in A:
                            return f"NOT {A[-1]}"
                        else:
                            return f"{A[-1]}"
                #else:
                    #if "NOT" in B:
                        #if "NOT" not in A:
                            #return f"NOT {A[-1]}"
                        #else:
                            #return f"{A[-1]}"

        return None


def main1():
    logic = LogicalResolution()

    # Добавляем утверждения
    logic.add_statement("NOT A => B")
    logic.add_statement("B => NOT C")
    logic.add_statement("NOT A")
    logic.add_statement("C")


    # Проверяем на противоречия
    logic.resolve()

def main2():
    logic = LogicalResolution()

    # Добавляем утверждения
    logic.add_statement("A => B")
    logic.add_statement("B => C")
    logic.add_statement("A")
    logic.add_statement("NOT C")


    # Проверяем на противоречия
    logic.resolve()


if __name__ == "__main__":
    main1()
    main2()
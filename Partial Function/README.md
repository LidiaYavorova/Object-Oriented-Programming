# Условие – Частични Функции

Разглеждаме абстрактен базов клас **Частична Функция**, който преобразува цели 32-битови числа в цели 32-битови числа и задължително притежава:
- операция за проверка дали функцията е дефинирана за дадена точка;
- операция за пресмятане на резултата на функцията за подадено `x`.

## Задача

Да се реализират следните конкретни наследници на абстрактния базов клас **Частична функция**:

### 1. Частична функция по критерий
В конструктора се подава **функция (или обект, който се държи като такава)**, която по подадено ѝ като аргумент число, връща **наредена двойка** – дали функцията е дефинирана там и ако да, какъв е резултатът.

### 2. Максимум на частични функции
В конструктора се подават няколко частични функции. Създаденият обект е дефиниран в дадена точка **само ако всички подадени функции са дефинирани в нея**.  
Резултатът за дадено `x` ще бъде **максимумът** от резултатите на подадените функции за `x`.

### 3. Минимум на частични функции
Също като горния случай, но резултатът за дадено `x` ще бъде **минимумът** от резултатите.

---

## Изискване

Да се реализира програма, която чете от **двоичен файл `func.dat`** информация за частична функция и конструира нова частична функция съгласно указаните в двоичния файл правила.

В началото на двоичния файл има две цели неотрицателни **16-битови числа `N` и `T`**, за които:

- `N <= 32`
- `T` определя какво следва и как се конструира функцията.

---

### Видове `T` и какво следва в двоичния файл:

#### `T = 0`
Следват **2N цели 32-битови числа**, които определят функцията:
Функцията е дефинирана **само** в подадените аргументи.

#### `T = 1`
Следват **N цели 32-битови числа**, в които функцията **не е дефинирана**.  
За всички останали x, функцията връща `x`.

#### `T = 2`
Следват **N цели 32-битови числа**, в които функцията връща `1`.  
Във всички други случаи – `0`.  
Функцията е дефинирана **навсякъде**.

#### `T = 3`
Следват **N низа**, всеки завършващ с `\0`, представляващи **пътища до двоични файлове**.  
Всеки файл описва частична функция. **Максимумът** от тези функции е текущата функция.

#### `T = 4`
Както при `T = 3`, но взимаме **минимума** от подадените частични функции.

---

## Режими на работа

1. Програмата приема от стандартния вход две цели числа `a` и `b` и извежда резултатите от функцията за всички числа в интервала `[a; b]`.

2. Позволява **последователно генериране** на резултат за всяка дефинирана точка, като следващият резултат се генерира **при поискване от потребителя**.

---

## Обработка на грешки

Програмата да обработва подходящо грешки, свързани с:
- некоректен вход,
- липсващи или повредени файлове,
- липса на дефиниция в дадена точка и др.







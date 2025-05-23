# ModifiableIntegerFunction

**ModifiableIntegerFunction** е клас, който реализира цели функции върху `int16_t` с възможност за модификация и изключване на точки от дефиниционното множество. Поддържа различни аритметични операции, композиция, проверка на свойства като инжективност и сюрективност, и запис/четене от файл.

---

## Основна идея

Функцията се реализира с помощта на два масива:

- `int16_t* result` – пази стойността на функцията за всеки възможен `int16_t` вход.
- `bool* isExcluded` – указва дали съответната стойност е изключена от дефиниционното множество.

---

## Конструктори и оператори

| Метод | Описание |
|-------|----------|
| `ModifiableIntegerFunction()` | Създава функция, дефинирана навсякъде със стойност 0. |
| `ModifiableIntegerFunction(int16_t (*f)(int16_t))` | Създава функция от подадена C-style функция. |
| `operator()` | Извиква функцията с даден аргумент `f(x)`. |
| `operator=` | Присвояване. |
| Копи-конструктор | Дълбоко копиране на друга функция. |

---

## Методи за промяна

| Метод | Описание |
|-------|----------|
| `setSpecificValue(int16_t input, int16_t output)` | Задава стойността на функцията за дадена входна стойност. |
| `exclusionOfPoint(int16_t input)` | Изключва дадена точка от дефиниционното множество. |

---

## Аритметични и композиционни оператори

| Оператор | Описание |
|----------|----------|
| `operator+` | Събиране: `(f + g)(x) = f(x) + g(x)` |
| `operator-` | Изваждане: `(f - g)(x) = f(x) - g(x)` |
| `operator*` | Композиция: `(f * g)(x) = f(g(x))` |
| `operator^` | Повдигане на степен: `f^k(x) = f(f(...f(x)))` (k пъти) <br> `f^-1(x)` връща обратна функция, ако съществува |

---

## Проверка на свойства

| Метод | Описание |
|-------|----------|
| `isInjection()` | Проверява дали функцията е инжективна (еднозначна). |
| `isSurjection()` | Проверява дали функцията е сюрективна (пълна). |
| `isBijection()` | Проверява дали функцията е биективна (едновременно инжективна и сюрективна). |

---

## Сравнение на функции

| Оператор | Описание |
|----------|----------|
| `==` | Проверява дали две функции са "паралелни" (разликата им е една и съща за всички точки). |
| `<`, `>`, `<=`, `>=` | Проверяват дали стойностите на едната функция са по-малки/големи от тези на другата във всички дефинирани точки. |

---

## Работа с файлове

| Метод | Описание |
|-------|----------|
| `writeToFile(const char* fileName)` | Записва функцията в бинарен файл. |
| `readFromFile(const char* fileName)` | Зарежда функция от бинарен файл. |

---

## Пример за използване

```cpp
int16_t square(int16_t x) {
    return x * x;
}

ModifiableIntegerFunction f(square);
f.setSpecificValue(5, 42);
f.exclusionOfPoint(3);

std::cout << "f(5) = " << f(5) << std::endl;

ModifiableIntegerFunction g([](int16_t x) { return x + 1; });
ModifiableIntegerFunction composition = f * g;

std::cout << "f(g(5)) = " << composition(5) << std::endl;

if (f.isInjection()) {
    std::cout << "f is injective!" << std::endl;
}

# MultiSet – Битово представяне на мултимножества

Проект, реализиращ структура от данни **MultiSet** – множество от цели числа с **повторения**, представено чрез **битово кодиране в масив от байтове**.

## Условие на задачата

Да се реализира клас `MultiSet`, който позволява работа с множество от `n` елемента (от 0 до `n - 1`), където всяко число може да се среща до `k` пъти. Структурата използва **bitmap** (битов масив), в който за всяко число се заделят достатъчно битове за представяне на стойност от 0 до `k`.

Класът трябва да поддържа следната функционалност:

### Основни операции
- `MultiSet(unsigned n, uint8_t k)` – създаване на множество с `n` възможни елемента и до `k` срещания на всяко.
- `void add(unsigned num)` – добавяне на едно срещане на елемента `num`.
- `unsigned countOccurrences(unsigned num) const` – брой срещания на елемент.
- `void print() const` – отпечатване на всички елементи и техния брой.
- `void printInMemoryLook() const` – отпечатване на битовото представяне на множеството.

### Работа с файлове
- `void serialize(const char* fileName) const` – сериализиране на множеството във файл.
- `void deserialize(const char* fileName)` – зареждане на множество от файл.

### Операции с множества
- `intersectionOfMultiSets(const MultiSet&, const MultiSet&)` – сечение на две мултимножества.
- `differenceOfMultiSets(const MultiSet&, const MultiSet&)` – разлика между две мултимножества.
- `additionOfMultiSet(const MultiSet&)` – удвояване на срещанията на всеки елемент (до максимум `k`).

## Пример за използване

```cpp
MultiSet m1(10, 3);
m1.add(2);
m1.add(2);
m1.add(5);
m1.print(); // Изход: 2: 2 пъти, 5: 1 път

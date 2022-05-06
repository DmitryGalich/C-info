# Память

## **Виртуальная память и страничаня организация памяти**
https://ru.bmstu.wiki/%D0%92%D0%B8%D1%80%D1%82%D1%83%D0%B0%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D1%8C_(%D0%9E%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%BE%D0%BD%D0%BD%D1%8B%D0%B5_%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%8B)

## **Этапы преобразования из исходного кода в исполняемый файл**
https://habr.com/ru/post/478124/

## **Статическая и динамическкая библиотека**

Статическая библиотека это фактически архив объектных файлов, который используется в процессе статической линковки. В результате статической линковки из многих объектных файлов получается один исполняемый, запускается статическая линковка в момент создания исполняемого файла.

Динамическая библиотека это фактически исполняемый файл (т.е. DLL и EXE в Windows имеют одинаковый формат). Динамическая линковка запускается в момент создания процесса (когда вы запускаете исполняемый файл на выполнение), линкуются между собой несколько исполняемых файлов каждый раз, когда создается новый процесс. Так же возможна динамическая линковка уже после запуска, т.е. новая библиотека может быть подгружена в адресное пространство ужа работающего процесса.

## **RAII**
 Получение ресурса есть инициализация — в ООП — организация получения доступа к ресурсу в конструкторе, а освобождения — в деструкторе соответствующего класса. Достаточно реализовать управление памятью в конструкторах и деструкторах, а компилятор вызовет их автоматически.

## **В каком учатке памяти хранятся локальные, глобальные, статические переменные?**

**Стек**
* Ограниченные область видимости и время жизни
* При выходе из области видимости происходит автоматическое разрушение хранимых переменных
* Более высокая скорость выделения/освобождения памяти.

**Куча**
* Куча медленнее стека выделяет и освобождает ресурсы, автоматически не очищается (по крайней мере в стандартном C++)
* Подвержена фрагментации
* Время жизни переменной не ограничено процессом выполнения
* Без явного вызова delete переменная будет существовать до конца выполнения программы.
* Зная адрес переменной в куче, к ней можно получить доступ из любой области видимости.
* Куча в некотором смысле "резиновая". В отличие от стека, она ограничена только физически.

## **Сколько памяти занимает класс**

To a first order approximation, the size of an object is the sum of the sizes of its constituent data members. You can be sure it will never be smaller than this.

More precisely, the compiler is entitled to insert padding space between data members to ensure that each data member meets the alignment requirements of the platform. Some platforms are very strict about alignment, while others (x86) are more forgiving, but will perform significantly better with proper alignment. So, even the compiler optimization setting can affect the object size.

Inheritance and virtual functions add an additional complication. As others have said, the member functions of your class themselves do not take up "per object" space, but the existence of virtual functions in that class's interface generally implies the existence of a virtual table, essentially a lookup table of function pointers used to dynamically resolve the proper function implementation to call at runtime. The virtual table (vtbl) is accessed generally via a pointer stored in each object.

Derived class objects also include all data members of their base classes.

Finally, access specifiers (public, private, protected) grant the compiler certain leeway with packing of data members.

The short answer is that sizeof(myObj) or sizeof(MyClass) will always tell you the proper size of an object, but its result is not always easy to predict.

## **Указатель на функцию. Как использовать?**
https://metanit.com/cpp/tutorial/4.8.php#:~:text=%D0%A3%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%20%D0%BD%D0%B0%20%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8E%20(function%20pointer,%D0%B8%20%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B0%D1%82%D1%8C%20%D1%80%D0%B5%D0%B7%D1%83%D0%BB%D1%8C%D1%82%D0%B0%D1%82%20%D0%B5%D0%B5%20%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B.

Умные указатели \
Итераторы \
std::move() \
std::optional \
rvalue и lvalue \
Операторы приведения типов. cast. Разница. Если dynamic_cast не может выполнить приведение, то что происходит? \
Сколько места занимает указатель? \
Сколько занимают типы данных? \
Type traits \
Битовые поля \
Битовые операции \
Big endian, little endian, middle endian \
Decltype. Чем отличается от auto? \
Ключевое слово __fastcall. Как обычно на низком уровне передаются параметры функции в при вызове функции \
Две функции для идентификации типа во времени выполнения программы(RTTI) \
Идеальная передача (Perfect forwarding) \

## **SFINAE**
https://thewolfsound.com/sfinae-substitution-failure-is-not-an-error/ \
https://www.youtube.com/watch?v=mNxAqLVIaW0 \
https://habr.com/ru/post/205772/ 

Отложенная инициализация(lazy initialization) \
Статическая и динамическкая библиотека

## ООП
Базовые принципы ООП: наследование, инкапсуляция, абстракция, полиморфизм \
Виды конструкторов и операторов в классе \
Указатель this. Каким образом метод получает доступ к this? \
Список инициализации в классе. В каком порядке инициализируются поля класса? \
Разница между перегрузкой и переопределением \
Разница между class и struct \
Mutable \
Volatile \
Explicit \
Сколько весит пустой класс? \
Сколько будет занимать класс с определёнными переменными(Альфа-банк) \
Типы инициализации переменной \
Можно ли перегрузить new и delete? В чём смысл? \
new placement \
Что происходит, если new не может выделить память? Какое исключение бросает? Что сделать, чтобы не бросало? \
SOLID \
Абстрактный класс. Есть ли разница между абстрактным классом и интерфейсом? \
Таблица виртуальных методов \
Выравнивание памяти в классах/структурах \
Plain old data(POD). Как сделать POD-классы/структуры \
Свойство, которым должен обладать объект, чтобы можно было добавить в ассоциативный контейнер \
Виртуальное наследование

## Контейнеры
Строение, сложность взаимодейсвия \
Коллизия в хэш-таблицах \
В каких контейнерах внутри чёрно-красное дерево? \
Хэш-таблица? \
Сложность вставки, удаления, поиска в базовые контейнеры

## Алгоритмы
Сложность и реализация базовых алгоритмов, деревья

## Многопоточность
Примитивы синхронизации мнопоточных приложений \
Разница mutex от семафора \
deadlock, состояние гонки \
Отличие процесса от потока \
Виды guard-ов \
condition variable \
https://habr.com/ru/post/517918/

## Функции
Рекурсия. К каким ошибкам может привести \
Лямбда-функции. Захват переменных. Функторы. Можно ли по ссылке захватить указатель this? \
Переменное(не фиксированное) количество параметров в функции \
Функции обратного вызова (callback function) \
Шаблоны. Нефиксированное число аргументов

## Подходы
DRY \
KISS \
PIMPL \
Безымянное пространство имён \
Паттерны

## Разное
Коорутины \
YAGNI \
One definition rule

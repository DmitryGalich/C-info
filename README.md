# C++ конспект

## Этапы преобразования из исходного кода в исполняемый файл

## Память

***RAII*** - (Получение ресурса есть инициализация) — в ООП — организация получения доступа к ресурсу в конструкторе, а освобождения — в деструкторе соответствующего класса. Достаточно реализовать управление памятью в конструкторах и деструкторах, а компилятор вызовет их автоматически.

Модель памяти приложения \
В каком учатке памяти хранятся локальные, глобальные, статические переменные? \
Указатель на функцию. Как использовать? \
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
SFINAE \
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
condition variable
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

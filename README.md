# Память

## **Виртуальная память и страничаня организация памяти**

<https://ru.bmstu.wiki/%D0%92%D0%B8%D1%80%D1%82%D1%83%D0%B0%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D1%8C_(%D0%9E%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%BE%D0%BD%D0%BD%D1%8B%D0%B5_%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%8B>)

## **Этапы преобразования из исходного кода в исполняемый файл**

<https://habr.com/ru/post/478124/>

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

В первом приближении размер объекта представляет собой сумму размеров составляющих его элементов данных. Вы можете быть уверены, что он никогда не будет меньше, чем это.

Точнее, компилятор имеет право вставлять пробел между элементами данных, чтобы гарантировать, что каждый элемент данных соответствует требованиям платформы к выравниванию. Некоторые платформы очень строго относятся к выравниванию, в то время как другие (x86) более снисходительны, но будут работать значительно лучше при правильном выравнивании. Таким образом, даже настройка оптимизации компилятора может повлиять на размер объекта.

Наследование и виртуальные функции добавляют дополнительную сложность. Как уже говорили другие, сами функции-члены вашего класса не занимают пространство «для каждого объекта», но существование виртуальных функций в интерфейсе этого класса обычно подразумевает существование виртуальной таблицы, по сути таблицы поиска указателей функций, используемых для динамически разрешать правильную реализацию функции для вызова во время выполнения. Доступ к виртуальной таблице (vtbl) обычно осуществляется через указатель, хранящийся в каждом объекте.

Объекты производного класса также включают в себя все элементы данных своих базовых классов.

Наконец, спецификаторы доступа (```public, private, protected```) предоставляют компилятору определенную свободу действий при упаковке элементов данных.

Короткий ответ заключается в том, что ```sizeof(myObj)``` или ```sizeof(MyClass)``` всегда будут указывать правильный размер объекта, но его результат не всегда легко предсказать.

## **Указатель на функцию. Как использовать?**

<https://metanit.com/cpp/tutorial/4.8.php#:~:text=%D0%A3%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%20%D0%BD%D0%B0%20%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8E%20(function%20pointer,%D0%B8%20%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B0%D1%82%D1%8C%20%D1%80%D0%B5%D0%B7%D1%83%D0%BB%D1%8C%D1%82%D0%B0%D1%82%20%D0%B5%D0%B5%20%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B>.

## **Умные указатели**

* ```unique_ptr``` представляет исключительное владение: может быть только один ```unique_ptr```, указывающий на объект. и этот объект удаляется при уничтожении указателя unique_ptr.
* ```shared_ptr``` представляет совместное владение: может иметься много указателей ```shared_ptr```, указывающих на объект, и объект удаляется только при уничтожении последнего указателя ```shared_ptr```.
* ```weak_ptr``` -  ```shared_ptr``` без счётчика

## **Итераторы**

* Итератор указывает (ссылается) на элемент последовательности (или за последний элемент).
* Два итератора можно сравнивать с помощью операторов ```=``` и ```! =```
* Значение элемента, на который указывает итератор, можно получить с помощью унарного оператора * ("разыменование").
* Итератор на следующий элемент можно получить с помощью оператора ```++```.
* Итераторы используются в качестве средства связи между нашим кодом
(алгоритмами) и нашими данными .

## **rvalue и lvalue**

По семантике lvalue ссылка формируется путём помещая & после некоторого типа.

```C++
A a;
A& a_ref1 = a;  // это lvalue ссылка
```

Если после некоторого типа поместить &&, то получится rvalue ссылка.

* Временный объект
* Объект без имени
* Объект без адреса

```C++
A a;
A&& a_ref2 = a;  // это rvalue ссылка
```

Rvalue ссылка ведет себя точно так же, как и lvalue ссылка, за исключением того, что она может быть связана с временным объектом, тогда как lvalue связать с временным (не константным) объектом нельзя.

```C++
A&  a_ref3 = A();  // Ошибка!
A&& a_ref4 = A();  // Ok
```

## **std::move()**

Функция ```std::move``` в действительности выполняет весьма скромную работу. Её задача состоит в том, чтобы принять либо lvalue, либо rvalue параметр, и вернуть его как rvalue без вызова конструктора копирования:

## **Шаблоны**

<https://habr.com/ru/post/436880/>

## **Идеальная передача (Perfect forwarding)**

<https://en.cppreference.com/w/cpp/utility/forward>
<https://www.modernescpp.com/index.php/perfect-forwarding>

## **std::optional**

<https://en.cppreference.com/w/cpp/utility/optional> \
Как ```nullptr```, только для неуказателей.

## **Операторы приведения типов**

<https://habr.com/ru/post/106294/>

Если у ```dynamic_cast``` не получается выполнить преобразование, то бросается исключение ```std::bad_cast```, а если указатель - будет возвращён 0. Используется RTTI.

## **Const**

```C++
#define KEK 12 // Просто подставляет текст 12 всюду, где написано KEK. Нет проверки при компиляции 

const int Constant1 = 96; // Постоянное значение типа int

const int * Constant2; // Указатель на постоянное значение типа int
int const * Constant2; // Указатель на постоянное значение типа int

int * const Constant3; // Постоянный указатель на некоторую переменную int. Т. е. значение указателя будет всегда неизменным, а значение переменной, на которую указывает указатель, менять можно.

int const * const Constant4; // Постоянным указатель, указывающий на постоянный int.

const char *Function1() { return "KEK"; } // Функция, возвращающая постоянную строку
```

## **Сколько места занимает указатель?**

Указатель указывает на место в памяти, поэтому он будет 32-битным в 32-битной системе и 64-битным в 64-битной системе. Размер указателя также не имеет отношения к типу, на который он указывает, и может быть измерен с помощью sizeof(anyType*).
В таких случаях, как указатели на таблицу виртуальных методов, размер указателя будет отличаться, и, согласно этой [статье](https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible), он будет различаться на разных платформах и даже на разных компиляторах на одной платформе. В моем случае, например (x64 ubuntu, GCC 4.6.3) он равен 16 байтам.

## **Виртуальная таблица**

<https://radioprog.ru/post/1279>

## **Сколько занимают типы данных?**

<https://metanit.com/cpp/tutorial/2.3.php>
<https://docs.microsoft.com/ru-ru/cpp/cpp/data-type-ranges?view=msvc-170>

## **Битовые поля**

<https://learnc.info/c/unions_and_bitfields.html>

## **Битовые операции**

<http://mycpp.ru/cpp/book/c04_11.html>

## **Порядок байтов**

<https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D1%80%D1%8F%D0%B4%D0%BE%D0%BA_%D0%B1%D0%B0%D0%B9%D1%82%D0%BE%D0%B2>

## **CV квалификаторы**

<https://ru.stackoverflow.com/questions/483673/%D0%A1%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80-%D0%B8-%D0%BA%D0%B2%D0%B0%D0%BB%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80> \
<https://bestprogrammer.ru/programmirovanie-i-razrabotka/kvalifikatory-c-i-spetsifikatory-klassov-hraneniya>

Decltype. Чем отличается от auto? \
Ключевое слово __fastcall. Как обычно на низком уровне передаются параметры функции в при вызове функции \
Две функции для идентификации типа во времени выполнения программы(RTTI) \

## **SFINAE**

<https://thewolfsound.com/sfinae-substitution-failure-is-not-an-error/> \
<https://www.youtube.com/watch?v=mNxAqLVIaW0> \
<https://habr.com/ru/post/205772/>

Отложенная инициализация(lazy initialization) \
Статическая и динамическкая библиотека

## ООП

## **Типы конструкторов**

```C++

class Buffer
{
public:
    Buffer(const std::string& buff)
    :   pBuff(nullptr)
    ,   buffSize(buff.length())
    {
        pBuff = new char[buffSize];
        memcpy(pBuff, buff.c_str(), buffSize);
    }

    ~Buffer(){ destroy(); }

    Buffer(const Buffer& other)
    :   pBuff(nullptr)
    ,   buffSize(other.buffSize)
    {
        pBuff = new char[buffSize];
        memcpy(pBuff, other.pBuff, buffSize);
    }

    Buffer& operator=(const Buffer& other)
    {
        destroy();
        buffSize = other.buffSize;
        pBuff = new char[buffSize];
        memcpy(pBuff, other.pBuff, buffSize);
        return *this;
    }

    Buffer(Buffer&& tmp)
    :   pBuff(tmp.pBuff)
    ,   buffSize(tmp.buffSize)
    {
        tmp.pBuff = nullptr;
    }

    Buffer& operator=(Buffer&& tmp)
    {
        destroy();
        buffSize = tmp.buffSize;
        pBuff = tmp.pBuff;
        tmp.pBuff = nullptr;
        return *this;
    }

private:
    void destroy()
    {
        if (pBuff)
            delete[] pBuff;
    }

    char* pBuff;
    size_t buffSize;
};


```

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
ООП, SOLID - <https://tproger.ru/translations/oop-principles-cheatsheet/#:~:text=%D0%91%D0%B0%D0%B7%D0%BE%D0%B2%D1%8B%D0%B5%20%D0%BF%D1%80%D0%B8%D0%BD%D1%86%D0%B8%D0%BF%D1%8B%20%D0%9E%D0%9E%D0%9F,%D0%BC%D0%B5%D1%85%D0%B0%D0%BD%D0%B8%D0%B7%D0%BC%20%D0%B4%D0%BB%D1%8F%20%D0%BF%D0%BE%D0%B2%D1%82%D0%BE%D1%80%D0%BD%D0%BE%D0%B3%D0%BE%20%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F%20%D0%BA%D0%BE%D0%B4%D0%B0>. \
Абстрактный класс. Есть ли разница между абстрактным классом и интерфейсом? \
Таблица виртуальных методов \
Выравнивание памяти в классах/структурах \
Plain old data(POD). Как сделать POD-классы/структуры \
Свойство, которым должен обладать объект, чтобы можно было добавить в ассоциативный контейнер \
Виртуальное наследование

## Шаблоны

Type traits \
Концепты \

## Контейнеры

Строение, сложность взаимодейсвия \
Коллизия в хэш-таблицах \
В каких контейнерах внутри чёрно-красное дерево? \
Хэш-таблица? \
Сложность вставки, удаления, поиска в базовые контейнеры

## Алгоритмы

Сложность и реализация базовых алгоритмов, деревья

```C++

void selectionSort(std::vector<int> &data) {
  int j = 0;
  int tmp = 0;

  for (int i = 0; i < data.size(); i++) {
    j = i;

    for (int k = i; k < data.size(); k++)
      if (data.at(j) > data.at(k))
        j = k;

    tmp = data.at(i);
    data[i] = data.at(j);
    data[j] = tmp;
  }
}

void selection_sort(std::vector<int> &data) {
  int current_minimum_index = 0;
  for (int i = 0; i < data.size(); i++) {
    current_minimum_index = i;

    for (int j = i; j < data.size(); j++) {
      if (data.at(current_minimum_index) > data.at(j))
        current_minimum_index = j;
    }

    std::swap(data.at(i), data.at(current_minimum_index));
  }
}

void bubbleSort(int data[], int lenD) {
  int tmp = 0;
  for (int i = 0; i < lenD; i++) {
    for (int j = (lenD - 1); j >= (i + 1); j--) {
      if (data[j] < data[j - 1]) {
        tmp = data[j];
        data[j] = data[j - 1];
        data[j - 1] = tmp;
      }
    }
  }
}

void bubble_sort(std::vector<int> &data) {
  bool is_sorted = false;

  while (!is_sorted) {
    is_sorted = true;

    for (int i = 0; i < data.size() - 1; i++) {
      if (data.at(i) > data.at(i + 1)) {
        std::swap(data.at(i), data.at(i + 1));
        is_sorted = false;
      }
    }
  }
}

void insertionSort(int data[], int lenD) {
  int key = 0;
  int i = 0;
  for (int j = 1; j < lenD; j++) {
    key = data[j];
    i = j - 1;
    while (i >= 0 && data[i] > key) {
      data[i + 1] = data[i];
      i = i - 1;
      data[i + 1] = key;
    }
  }
}

void insertion_sort(std::vector<int> &data) {
  for (int i = 1; i < data.size(); i++) {
    for (int j = i; j > 0; j--) {
      if (data.at(j) > data.at(j - 1))
        break;

      std::swap(data.at(j), data.at(j - 1));
    }
  }
}

void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR) {
  int i = 0;
  int j = 0;
  while (i < lenL || j < lenR) {
    if (i < lenL & j < lenR) {
      if (L[i] <= R[j]) {
        merged[i + j] = L[i];
        i++;
      } else {
        merged[i + j] = R[j];
        j++;
      }
    } else if (i < lenL) {
      merged[i + j] = L[i];
      i++;
    } else if (j < lenR) {
      merged[i + j] = R[j];
      j++;
    }
  }
}

void mergeSort(int data[], int lenD) {
  if (lenD > 1) {
    int middle = lenD / 2;
    int rem = lenD - middle;
    int *L = new int[middle];
    int *R = new int[rem];
    for (int i = 0; i < lenD; i++) {
      if (i < middle) {
        L[i] = data[i];
      } else {
        R[i - middle] = data[i];
      }
    }
    mergeSort(L, middle);
    mergeSort(R, rem);
    merge(data, lenD, L, middle, R, rem);
  }
}

void quickSort(int *data, int const len) {
  int const lenD = len;
  int pivot = 0;
  int ind = lenD / 2;
  int i, j = 0, k = 0;
  if (lenD > 1) {
    int *L = new int[lenD];
    int *R = new int[lenD];
    pivot = data[ind];
    for (i = 0; i < lenD; i++) {
      if (i != ind) {
        if (data[i] < pivot) {
          L[j] = data[i];
          j++;
        } else {
          R[k] = data[i];
          k++;
        }
      }
    }
    quickSort(L, j);
    quickSort(R, k);
    for (int cnt = 0; cnt < lenD; cnt++) {
      if (cnt < j) {
        data[cnt] = L[cnt];
      } else if (cnt == j) {
        data[cnt] = pivot;
      } else {
        data[cnt] = R[cnt - (j + 1)];
      }
    }
  }
}


```

## Многопоточность

Примитивы синхронизации мнопоточных приложений \
Разница mutex от семафора \
deadlock, состояние гонки \
Отличие процесса от потока \
Виды guard-ов \
condition variable \
<https://habr.com/ru/post/517918/>

## Функции

Рекурсия. К каким ошибкам может привести \
Лямбда-функции. Захват переменных. Функторы. Можно ли по ссылке захватить указатель this? \
Переменное(не фиксированное) количество параметров в функции \
Функции обратного вызова (callback function) \
Шаблоны. Нефиксированное число аргументов

## Подходы

DRY - Don't repeat yourself \
KISS - Keep it simple stupid \
PIMPL \
Безымянное пространство имён \
Паттерны

## Разное

Коорутины \
YAGNI \
One definition rule

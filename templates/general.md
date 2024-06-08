Шаблоны в C++ — это мощный инструмент, позволяющий писать обобщённый код, который может работать с различными типами данных без дублирования кода для каждого типа. Они особенно полезны для реализации обобщённых алгоритмов и структур данных, таких как списки, очереди, стеки и другие контейнеры.

### Основные виды шаблонов в C++

1. **Функциональные шаблоны**:
    Шаблоны функций позволяют создавать функции, которые могут работать с различными типами данных.

    ```cpp
    template <typename T>
    T add(T a, T b) {
        return a + b;
    }

    int main() {
        std::cout << add(3, 4) << std::endl;        // Вывод: 7
        std::cout << add(3.5, 2.1) << std::endl;    // Вывод: 5.6
        return 0;
    }
    ```

2. **Шаблоны классов**:
    Шаблоны классов позволяют создавать классы, которые могут работать с различными типами данных.

    ```cpp
    template <typename T>
    class Container {
    private:
        T value;
    public:
        Container(T v) : value(v) {}
        T getValue() const { return value; }
    };

    int main() {
        Container<int> intContainer(42);
        Container<std::string> stringContainer("Hello");

        std::cout << intContainer.getValue() << std::endl;         // Вывод: 42
        std::cout << stringContainer.getValue() << std::endl;      // Вывод: Hello
        return 0;
    }
    ```

3. **Шаблоны с несколькими параметрами**:
    Шаблоны могут принимать несколько параметров типов.

    ```cpp
    template <typename T, typename U>
    class Pair {
    private:
        T first;
        U second;
    public:
        Pair(T f, U s) : first(f), second(s) {}
        T getFirst() const { return first; }
        U getSecond() const { return second; }
    };

    int main() {
        Pair<int, double> p(42, 3.14);
        std::cout << p.getFirst() << ", " << p.getSecond() << std::endl; // Вывод: 42, 3.14
        return 0;
    }
    ```

4. **Шаблоны с параметрами по умолчанию**:
    Шаблоны могут иметь параметры по умолчанию.

    ```cpp
    template <typename T = int>
    class DefaultContainer {
    private:
        T value;
    public:
        DefaultContainer(T v = 0) : value(v) {}
        T getValue() const { return value; }
    };

    int main() {
        DefaultContainer<> defaultContainer;    // Использует тип int по умолчанию
        std::cout << defaultContainer.getValue() << std::endl; // Вывод: 0
        return 0;
    }
    ```

5. **Шаблоны с параметрами-шаблонами**:
    Шаблоны могут принимать другие шаблоны в качестве параметров.

    ```cpp
    template <typename T>
    class Wrapper {
    private:
        T value;
    public:
        Wrapper(T v) : value(v) {}
        T getValue() const { return value; }
    };

    template <template <typename> class Container, typename T>
    class Holder {
    private:
        Container<T> container;
    public:
        Holder(T v) : container(v) {}
        T getValue() const { return container.getValue(); }
    };

    int main() {
        Holder<Wrapper, int> holder(42);
        std::cout << holder.getValue() << std::endl; // Вывод: 42
        return 0;
    }
    ```

### Примеры использования шаблонов

1. **Шаблоны стандартной библиотеки (STL)**:
    В стандартной библиотеке C++ (STL) многие контейнеры и алгоритмы реализованы с использованием шаблонов. Например, `std::vector`, `std::list`, `std::map`, `std::sort` и другие.

    ```cpp
    #include <vector>
    #include <algorithm>
    #include <iostream>

    int main() {
        std::vector<int> vec = {5, 2, 8, 1, 3};
        std::sort(vec.begin(), vec.end());

        for (int n : vec) {
            std::cout << n << " ";  // Вывод: 1 2 3 5 8
        }
        std::cout << std::endl;

        return 0;
    }
    ```

2. **Умные указатели**:
    Умные указатели, такие как `std::unique_ptr` и `std::shared_ptr`, тоже реализованы с использованием шаблонов.

    ```cpp
    #include <memory>
    #include <iostream>

    int main() {
        std::unique_ptr<int> p = std::make_unique<int>(42);
        std::cout << *p << std::endl;  // Вывод: 42
        return 0;
    }
    ```

### Заключение

Шаблоны являются основным механизмом для создания обобщённого кода в C++. Они повышают гибкость и повторное использование кода, позволяют реализовывать обобщённые алгоритмы и структуры данных, которые могут работать с любыми типами данных.

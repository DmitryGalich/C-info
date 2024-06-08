Move-семантика в C++ — это концепция, позволяющая перемещать ресурсы из одного объекта в другой вместо их копирования. Она была введена в стандарт C++11 для оптимизации производительности и управления ресурсами. Основные элементы move-семантики включают перемещающие конструкторы и перемещающие операторы присваивания.

### Основные концепции move-семантики

1. **Перемещающий конструктор**:
   - Перемещающий конструктор используется для переноса ресурсов из одного объекта в другой.
   - Синтаксис: `T(T&& other);`
   - В параметре используется rvalue-ссылка (`T&&`), указывающая, что объект может быть "украден".

2. **Перемещающий оператор присваивания**:
   - Перемещающий оператор присваивания используется для переноса ресурсов из одного объекта в другой при присваивании.
   - Синтаксис: `T& operator=(T&& other);`
   - Аналогично, используется rvalue-ссылка для указания на возможность переноса ресурсов.

### Пример использования

Рассмотрим класс, который управляет динамическим массивом:

```cpp
#include <iostream>
#include <utility> // для std::move

class DynamicArray {
private:
    int* data;
    size_t size;

public:
    // Конструктор
    DynamicArray(size_t size) : size(size), data(new int[size]) {
        std::cout << "Constructor called\n";
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
        std::cout << "Destructor called\n";
    }

    // Копирующий конструктор
    DynamicArray(const DynamicArray& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    // Перемещающий конструктор
    DynamicArray(DynamicArray&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        std::cout << "Move constructor called\n";
    }

    // Копирующий оператор присваивания
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;

        size = other.size;
        data = new int[other.size];
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy assignment operator called\n";
        return *this;
    }

    // Перемещающий оператор присваивания
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;

        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        std::cout << "Move assignment operator called\n";
        return *this;
    }
};

int main() {
    DynamicArray arr1(10);
    DynamicArray arr2 = std::move(arr1); // Вызов перемещающего конструктора

    DynamicArray arr3(20);
    arr3 = std::move(arr2); // Вызов перемещающего оператора присваивания

    return 0;
}
```

### Как это работает?

- **Перемещающий конструктор**:
  - В этом примере `DynamicArray(DynamicArray&& other) noexcept` переносит указатель на данные и размер из `other` в новый объект.
  - Затем `other` обнуляется, чтобы избежать двойного удаления ресурсов.

- **Перемещающий оператор присваивания**:
  - Сначала освобождаются текущие ресурсы объекта.
  - Затем ресурсы перемещаются из `other`, после чего `other` обнуляется аналогично конструктору.

### Преимущества move-семантики

- **Повышенная производительность**:
  - При перемещении объектов не требуется глубокое копирование данных, что экономит время и память.
- **Безопасность и управление ресурсами**:
  - Move-семантика гарантирует, что ресурсы корректно перемещаются и освобождаются, предотвращая утечки памяти.

Move-семантика особенно полезна при работе с временными объектами и контейнерами стандартной библиотеки, такими как `std::vector`, `std::string` и т.д., где копирование может быть дорогим.

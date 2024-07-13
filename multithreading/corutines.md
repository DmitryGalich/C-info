Корутин (coroutine) в C++ представляет собой специальный вид функции, выполнение которой можно приостанавливать и возобновлять в дальнейшем, что позволяет создавать более гибкие и эффективные асинхронные программы. В C++ корутины были введены в стандарте C++20. Они позволяют писать асинхронный код в более линейном стиле, избегая вложенности обратных вызовов (callback).

Вот основные понятия и примеры использования корутин в C++:

### Основные понятия

1. **co_await**: используется для приостановки выполнения корутины до тех пор, пока ожидаемое выражение не будет готово.
2. **co_return**: используется для возврата значения из корутины.
3. **co_yield**: используется для временной приостановки корутины и возврата значения.

### Простой пример корутины

Пример корутины, которая возвращает значения от 1 до 3 с помощью co_yield:

```cpp
#include <iostream>
#include <coroutine>

struct Generator {
    struct promise_type {
        int current_value;

        Generator get_return_object() {
            return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            std::exit(1);
        }
    };

    std::coroutine_handle<promise_type> coro;

    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}

    ~Generator() {
        if (coro) coro.destroy();
    }

    bool move_next() {
        coro.resume();
        return !coro.done();
    }

    int current_value() {
        return coro.promise().current_value;
    }
};

Generator generate_sequence() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

int main() {
    auto gen = generate_sequence();
    while (gen.move_next()) {
        std::cout << gen.current_value() << std::endl;
    }
    return 0;
}
```

### Разбор примера

1. **Структура `promise_type`**:
   - Отвечает за управление состоянием корутины.
   - `get_return_object` создает и возвращает объект корутины.
   - `initial_suspend` и `final_suspend` определяют поведение корутины при начальной и финальной приостановках.
   - `yield_value` используется для временной приостановки корутины с возвращением значения.
   - `return_void` используется для завершения корутины без возвращения значения.
   - `unhandled_exception` обрабатывает исключения.

2. **Структура `Generator`**:
   - Хранит дескриптор корутины (`std::coroutine_handle`).
   - `move_next` возобновляет выполнение корутины и проверяет, завершена ли она.
   - `current_value` возвращает текущее значение.

3. **Функция `generate_sequence`**:
   - Использует `co_yield` для приостановки выполнения и возврата значений.

### Полезные ссылки

- [Корутинная поддержка в C++20 на cppreference.com](https://en.cppreference.com/w/cpp/language/coroutines)
- [Документация C++20](https://isocpp.org/files/papers/N4860.pdf)

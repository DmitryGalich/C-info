C++ templates are a powerful feature of the language that allow you to write generic and reusable code. They enable the creation of functions, classes, and other data structures that can work with any data type. Here’s a comprehensive guide to various tricks and advanced techniques you can use with C++ templates:

### 1. Basic Templates

- **Function Templates:**

  ```cpp
  template<typename T>
  T max(T a, T b) {
      return (a > b) ? a : b;
  }
  ```

- **Class Templates:**

  ```cpp
  template<typename T>
  class MyClass {
      T data;
  public:
      MyClass(T data) : data(data) {}
      T getData() { return data; }
  };
  ```

### 2. Template Specialization

- **Full Specialization:**

  ```cpp
  template<>
  class MyClass<int> {
      int data;
  public:
      MyClass(int data) : data(data) {}
      int getData() { return data; }
  };
  ```

- **Partial Specialization:**

  ```cpp
  template<typename T>
  class MyClass<std::vector<T>> {
      std::vector<T> data;
  public:
      MyClass(std::vector<T> data) : data(data) {}
      std::vector<T> getData() { return data; }
  };
  ```

### 3. Template Non-Type Parameters

- **Example:**

  ```cpp
  template<int N>
  class Array {
      int arr[N];
  public:
      int size() { return N; }
  };
  ```

### 4. Variadic Templates

- **Function Variadic Templates:**

  ```cpp
  template<typename T>
  void print(T t) {
      std::cout << t << std::endl;
  }

  template<typename T, typename... Args>
  void print(T t, Args... args) {
      std::cout << t << ", ";
      print(args...);
  }
  ```

- **Class Variadic Templates:**

  ```cpp
  template<typename... Types>
  class Tuple;
  
  template<typename T, typename... Types>
  class Tuple<T, Types...> : public Tuple<Types...> {
      T head;
  public:
      Tuple(T t, Types... ts) : Tuple<Types...>(ts...), head(t) {}
      T getHead() { return head; }
  };
  
  template<>
  class Tuple<> {};
  ```

### 5. SFINAE (Substitution Failure Is Not An Error)

- **Example:**

  ```cpp
  template<typename T>
  typename std::enable_if<std::is_integral<T>::value, T>::type
  foo(T t) {
      return t;
  }
  ```

### 6. Template Metaprogramming

- **Factorial Computation:**

  ```cpp
  template<int N>
  struct Factorial {
      static const int value = N * Factorial<N - 1>::value;
  };

  template<>
  struct Factorial<0> {
      static const int value = 1;
  };
  ```

### 7. CRTP (Curiously Recurring Template Pattern)

- **Example:**

  ```cpp
  template<typename Derived>
  class Base {
  public:
      void interface() {
          static_cast<Derived*>(this)->implementation();
      }
  };

  class Derived : public Base<Derived> {
  public:
      void implementation() {
          std::cout << "Implementation in Derived" << std::endl;
      }
  };
  ```

### 8. Template Aliases

- **Example:**

  ```cpp
  template<typename T>
  using Vec = std::vector<T>;

  Vec<int> v; // equivalent to std::vector<int>
  ```

### 9. Concept-based Templates (C++20)

- **Example:**

  ```cpp
  template<typename T>
  concept Integral = std::is_integral_v<T>;

  template<Integral T>
  T add(T a, T b) {
      return a + b;
  }
  ```

### 10. Fold Expressions (C++17)

- **Example:**

  ```cpp
  template<typename... Args>
  auto sum(Args... args) {
      return (args + ...); // Fold expression
  }
  ```

### 11. Constexpr if (C++17)

- **Example:**

  ```cpp
  template<typename T>
  void printTypeInfo(T t) {
      if constexpr (std::is_integral_v<T>) {
          std::cout << "Type is integral" << std::endl;
      } else {
          std::cout << "Type is not integral" << std::endl;
      }
  }
  ```

These tricks and techniques showcase the flexibility and power of templates in C++. They allow for writing highly generic and efficient code, enabling better code reuse and maintainability.

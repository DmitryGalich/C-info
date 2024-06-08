Creating `shared_ptr` and `unique_ptr` from scratch in C++ involves understanding and implementing the core functionalities of these smart pointers, such as reference counting for `shared_ptr` and exclusive ownership for `unique_ptr`. Below are simplified versions of these smart pointers to illustrate their basic mechanisms.

### `unique_ptr` Implementation

A `unique_ptr` is a smart pointer that owns and manages another object through a pointer and disposes of that object when the `unique_ptr` goes out of scope. It ensures that only one `unique_ptr` can own the object at any given time.

```cpp
template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Constructor
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~unique_ptr() {
        delete ptr;
    }

    // Delete copy constructor and copy assignment
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Dereference operators
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

    // Release ownership
    T* release() {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }

    // Reset pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
```

### `shared_ptr` Implementation

This implementation introduces a control block that contains the shared reference count and the weak reference count.

```cpp
template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
private:
    T* ptr;
    struct ControlBlock {
        size_t shared_count;
        size_t weak_count;

        ControlBlock() : shared_count(1), weak_count(0) {}
    }* control;

    void release() {
        if (control) {
            if (--control->shared_count == 0) {
                delete ptr;
                if (control->weak_count == 0) {
                    delete control;
                }
            }
        }
    }

    void increase_shared_count() {
        if (control) {
            ++control->shared_count;
        }
    }

public:
    // Constructor
    explicit shared_ptr(T* p = nullptr)
        : ptr(p), control(p ? new ControlBlock() : nullptr) {}

    // Copy constructor
    shared_ptr(const shared_ptr& other)
        : ptr(other.ptr), control(other.control) {
        increase_shared_count();
    }

    // Move constructor
    shared_ptr(shared_ptr&& other) noexcept
        : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
    }

    // Copy assignment
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            increase_shared_count();
        }
        return *this;
    }

    // Move assignment
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    // Destructor
    ~shared_ptr() {
        release();
    }

    // Dereference operators
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

    // Get reference count
    size_t use_count() const {
        return control ? control->shared_count : 0;
    }

    // Check if unique
    bool unique() const {
        return use_count() == 1;
    }

    friend class weak_ptr<T>;
};

// Weak pointer implementation
template <typename T>
class weak_ptr {
private:
    T* ptr;
    typename shared_ptr<T>::ControlBlock* control;

    void release() {
        if (control) {
            if (--control->weak_count == 0 && control->shared_count == 0) {
                delete control;
            }
        }
    }

public:
    // Constructor
    weak_ptr() : ptr(nullptr), control(nullptr) {}

    // Constructor from shared_ptr
    weak_ptr(const shared_ptr<T>& sptr)
        : ptr(sptr.ptr), control(sptr.control) {
        if (control) {
            ++control->weak_count;
        }
    }

    // Copy constructor
    weak_ptr(const weak_ptr& other)
        : ptr(other.ptr), control(other.control) {
        if (control) {
            ++control->weak_count;
        }
    }

    // Move constructor
    weak_ptr(weak_ptr&& other) noexcept
        : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
    }

    // Copy assignment
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                ++control->weak_count;
            }
        }
        return *this;
    }

    // Move assignment
    weak_ptr& operator=(weak_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    // Destructor
    ~weak_ptr() {
        release();
    }

    // Convert to shared_ptr
    shared_ptr<T> lock() const {
        if (control && control->shared_count > 0) {
            return shared_ptr<T>(*this);
        }
        return shared_ptr<T>();
    }

    // Get reference count
    size_t use_count() const {
        return control ? control->shared_count : 0;
    }

    // Check if expired
    bool expired() const {
        return use_count() == 0;
    }
};
```

### Usage Example with `weak_ptr`

Here is a simple usage example for both `shared_ptr` and `weak_ptr`:

```cpp
#include <iostream>

int main() {
    // shared_ptr example
    shared_ptr<int> sptr1(new int(10));
    std::cout << "shared_ptr value: " << *sptr1 << std::endl;
    std::cout << "shared_ptr count: " << sptr1.use_count() << std::endl;

    weak_ptr<int> wptr1(sptr1);
    std::cout << "weak_ptr count: " << wptr1.use_count() << std::endl;
    std::cout << "weak_ptr expired: " << wptr1.expired() << std::endl;

    {
        shared_ptr<int> sptr2 = sptr1;
        std::cout << "shared_ptr value in new scope: " << *sptr2 << std::endl;
        std::cout << "shared_ptr count in new scope: " << sptr2.use_count() << std::endl;
    }

    std::cout << "shared_ptr count after scope: " << sptr1.use_count() << std::endl;

    shared_ptr<int> sptr3 = wptr1.lock();
    if (sptr3) {
        std::cout << "locked shared_ptr value: " << *sptr3 << std::endl;
    } else {
        std::cout << "weak_ptr expired, no shared_ptr available." << std::endl;
    }

    return 0;
}
```

This example demonstrates the interaction between `shared_ptr` and `weak_ptr`, showing how `weak_ptr` does not affect the reference count of the managed object but can be used to create a `shared_ptr` if the object is still alive.

#include <coroutine>
#include <iostream>
#include <optional>

class Task {
public:
    struct promise_type {
        Task get_return_object() {
            return Task{ Handle::from_promise(*this) };
        }
        static std::suspend_never initial_suspend() noexcept {
            return {};
        }
        static std::suspend_always final_suspend() noexcept {
            return {};
        }
        std::suspend_always yield_value(bool value) noexcept {
            current_value = std::move(value);
            return {};
        }
        void return_value(bool value) noexcept {
            current_value = std::move(value);
            return;
        }
        
        void await_transform() = delete;
        [[noreturn]]
        static void unhandled_exception() {
            throw;
        }

        std::optional<bool> get_value() {
            return current_value;
        }

        std::optional<bool> current_value;
    };

    using Handle = std::coroutine_handle<promise_type>;

    explicit Task(const Handle coroutine) :
        m_coroutine{ coroutine }
    {}

    Task() = default;
    ~Task() {
        if (m_coroutine) {
            m_coroutine.destroy();
        }
    }

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&& other) noexcept :
        m_coroutine{ other.m_coroutine }
    {
        other.m_coroutine = {};
    }
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (m_coroutine) {
                m_coroutine.destroy();
            }
            m_coroutine = other.m_coroutine;
            other.m_coroutine = {};
        }
        return *this;
    }

    std::optional<bool> next() {
        if (m_coroutine) {
            m_coroutine.resume();
            return m_coroutine.promise().get_value();
        }
        else {
            return {};
        }
    }

private:
    Handle m_coroutine;
};


//возвращаю булевские значения во-первых, для того чтобы main понимал, когда прекратить вызывать корутину,
// во-вторых, потому что компилятор не хочет принимать yield без возвращаемого значения и гугл говорит, что без аргумента yield не принимается
Task range() {
    std::cout << "Hello, World!" << std::endl;
    co_yield true;
    std::cout << "I am coroutine!" << std::endl;
    co_yield true;
    std::cout << "Nice to meet you!" << std::endl;
    co_yield true;
    std::cout << "Goodbye!" << std::endl;
    co_return false;
}

int main() {
    auto x = range();
    int i = 1;
    while (*x.next()) {
    }
    std::cout << "end\n";
}


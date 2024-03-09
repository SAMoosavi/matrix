#include "Matrix.h"
#include "concept.h"
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;


template<Containerable Container, typename Element = typename Container::value_type>
requires Multiplicationable<Element> && AssignSumable<Element>
constexpr Element multiplication(const Container &lhs, const Container &rhs) {
    if (lhs.size() != rhs.size()) throw invalid_argument("Cannot multiply spans of different sizes");
    Element result{};
    for (size_t i = 0; i < lhs.size(); ++i)
        result += lhs[i] * rhs[i];

    return result;
}

template<Containerable Container, typename Element = typename Container::value_type>
constexpr Element operator*(const Container &lhs, const Container &rhs) {
    return multiplication(lhs, rhs);
}

template<Containerable Container, typename Element = typename Container::value_type>
requires Sumable<Element>
constexpr Container sum(const Container &lhs, const Container &rhs) {
    if (lhs.size() != rhs.size()) throw invalid_argument("Cannot sum spans of different sizes");
    Container result(lhs.size());
    if constexpr (ranges::range<Element>) {
        for (size_t index = 0; index < lhs.size(); ++index)
            result[index] = rhs[index] + lhs[index];
    } else if constexpr (Sumable<Element>) {
        for (size_t index = 0; index < lhs.size(); ++index)
            result[index] = rhs[index] + lhs[index];
    } else {
        throw std::invalid_argument("invalid type of Container::value_type");
    }
    return result;
}

template<Containerable Container, typename Element = typename Container::value_type>
constexpr Container operator+(const Container &lhs, const Container &rhs) {
    return sum(lhs, rhs);
}


class W {
public:
    W() : num(0) {}

    W(int num) : num(num) {}

    W operator*(const W &other) const { return W{num * other.num}; }

    W operator+(const W &other) const { return W{num + other.num}; }

    W &operator+=(const W &other) {
        num += other.num;
        return *this;
    }

    W &operator*=(const W &other) {
        num *= other.num;
        return *this;
    }

    [[nodiscard]] int get() const { return num; }

private:
    int num;
};


template<typename T>
void print(const T &a) {
    if constexpr (ranges::range<T>)
        for (const auto &aa: a)
            print(aa);
    else
        cout << a.get() << endl;
}

int main() {
    vector<vector<W>> a = {{1, 2, 3, 4, 5},
                           {1, 2, 3, 4, 5},
                           {1, 2, 3, 4, 5},
                           {1, 2, 3, 4, 5}};
    Matrix<W> v1(a);
    Matrix<W> v2 = v1;

//    Matrix<W> po = v1 + v2;
    print(v1.get_table());
//    cout << po << endl;
    return 0;
}

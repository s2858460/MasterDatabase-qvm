#ifndef BOOST_QVM_TEST_QVM_HPP_INCLUDED
#define BOOST_QVM_TEST_QVM_HPP_INCLUDED

#include <catch2/catch_all.hpp>
#include <cmath>

#define BOOST_QVM_TEST_EQ(x,y) \
    REQUIRE(::test_qvm::detail::test_eq_impl((x),(y)))

#define BOOST_QVM_TEST_NEQ(x,y) \
    REQUIRE(::test_qvm::detail::test_neq_impl((x),(y)))

#define BOOST_QVM_TEST_CLOSE(x,y,t) \
    REQUIRE(::test_qvm::detail::test_close_impl((x),(y),(t)))

#define BOOST_QVM_TEST_EQ_QUAT(x,y) \
    REQUIRE(::test_qvm::detail::test_eq_q_impl((x),(y)))

#define BOOST_QVM_TEST_NEQ_QUAT(x,y) \
    REQUIRE(::test_qvm::detail::test_neq_q_impl((x),(y)))

#define BOOST_QVM_TEST_CLOSE_QUAT(x,y,t) \
    REQUIRE(::test_qvm::detail::test_close_q_impl((x),(y),(t)))

#define BOOST_TEST REQUIRE
#define BOOST_TEST_EQ(x, y) REQUIRE((x) == (y))
#define BOOST_TEST_NE(x, y) REQUIRE((x) != (y))
#define BOOST_TEST_LT(x, y) REQUIRE((x) < (y))

namespace test_qvm {
    namespace detail {
        // ------------------------------------------------------------
        // tolerance
        // ------------------------------------------------------------
        inline bool close_at_tolerance(float a, float b, float tolerance) {
            return std::abs(a - b) <= tolerance * std::max(std::abs(a), std::abs(b));
        }

        inline bool close_at_tolerance(double a, double b, double tolerance) {
            return std::abs(a - b) <= tolerance * std::max(std::abs(a), std::abs(b));
        }

        // ------------------------------------------------------------
        // EQ
        // ------------------------------------------------------------
        template <class A, class B>
        bool test_eq_impl(A const& a, B const& b) {
            using namespace ::boost::qvm;
            return a == b;
        }

        template <class A, class B, int M, int N>
        bool test_eq_impl(A(&a)[M][N], B(&b)[M][N]) {
            using namespace ::boost::qvm;
            for (int i = 0; i < M; ++i)
                for (int j = 0; j < N; ++j)
                    if (!(a[i][j] == b[i][j]))
                        return false;
            return true;
        }

        template <class A, class B, int D>
        bool test_eq_impl(A(&a)[D], B(&b)[D]) {
            using namespace ::boost::qvm;
            for (int i = 0; i < D; ++i)
                if (!(a[i] == b[i]))
                    return false;
            return true;
        }

        template <class A, class B>
        bool test_eq_q_impl(A(&a)[4], B(&b)[4]) {
            using namespace ::boost::qvm;

            bool same = true;
            for (int i = 0; i < 4; ++i)
                if (!(a[i] == b[i]))
                    same = false;

            if (same) return true;

            for (int i = 0; i < 4; ++i)
                if (!(a[i] == -b[i]))
                    return false;

            return true;
        }

        // ------------------------------------------------------------
        // NEQ
        // ------------------------------------------------------------
        template <class A, class B>
        bool test_neq_impl(A const& a, B const& b) {
            using namespace ::boost::qvm;
            return a != b;
        }

        template <class A, class B, int M, int N>
        bool test_neq_impl(A(&a)[M][N], B(&b)[M][N]) {
            using namespace ::boost::qvm;
            for (int i = 0; i < M; ++i)
                for (int j = 0; j < N; ++j)
                    if (a[i][j] != b[i][j])
                        return true;
            return false;
        }

        template <class A, class B, int D>
        bool test_neq_impl(A(&a)[D], B(&b)[D]) {
            using namespace ::boost::qvm;
            for (int i = 0; i < D; ++i)
                if (a[i] != b[i])
                    return true;
            return false;
        }

        template <class A, class B>
        bool test_neq_q_impl(A(&a)[4], B(&b)[4]) {
            using namespace ::boost::qvm;

            bool all_diff = true;
            for (int i = 0; i < 4; ++i)
                if (!(a[i] != b[i]))
                    all_diff = false;

            if (all_diff) return true;

            for (int i = 0; i < 4; ++i)
                if (!(a[i] != -b[i]))
                    return false;

            return true;
        }

        // ------------------------------------------------------------
        // CLOSE
        // ------------------------------------------------------------
        template <class A, class B, class T>
        bool test_close_impl(A a, B b, T t) {
            return close_at_tolerance(a, b, t);
        }

        template <class A, class B, class T, int M, int N>
        bool test_close_impl(A(&a)[M][N], B(&b)[M][N], T t) {
            for (int i = 0; i < M; ++i)
                for (int j = 0; j < N; ++j)
                    if (!close_at_tolerance(a[i][j], b[i][j], t))
                        return false;
            return true;
        }

        template <class A, class B, class T, int D>
        bool test_close_impl(A(&a)[D], B(&b)[D], T t) {
            for (int i = 0; i < D; ++i)
                if (!close_at_tolerance(a[i], b[i], t))
                    return false;
            return true;
        }

        template <class A, class B, class T>
        bool test_close_q_impl(A(&a)[4], B(&b)[4], T t) {
            bool same = true;
            for (int i = 0; i < 4; ++i)
                if (!close_at_tolerance(a[i], b[i], t))
                    same = false;

            if (same) return true;

            for (int i = 0; i < 4; ++i)
                if (!close_at_tolerance(a[i], -b[i], t))
                    return false;

            return true;
        }

    } // namespace detail
} // namespace test_qvm

#endif
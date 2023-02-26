#include <vector>
#include <iostream>
#include <assert.h>

/**
 * @brief 
 * @tparam T 
 */

template <typename T>
class SegmentTree
{
public:
    std::vector<T> st;
    T (*op)(T, T);
    T (*f)(T) = nullptr;
    int size;

    template <typename RandomAccessIterator>
    T build_from(int pos,
                 RandomAccessIterator left, 
                 RandomAccessIterator right
                 )
    {
        if (left + 1 == right)
        {
            if (this->f == nullptr)
            {
                st[pos] = *left;
            } else 
            {
                st[pos] = this->f(*left);
            }
            return st[pos];
        }
        else
        {
            RandomAccessIterator mid = left + (right - left) / 2;
            T left_res = this->build_from(2 * pos + 1, left, mid);
            T right_res = this->build_from(2 * pos + 2, mid, right);
            st[pos] = this->op(left_res, right_res);
            return st[pos];
        }
    }

    template <typename RandomAccessIterator>
    SegmentTree(RandomAccessIterator first,
                RandomAccessIterator last,
                T (*op)(T, T),
                T (*f)(T) = nullptr)
    {
        // FACT: A segment tree has at most 4*n nodes
        this->st.resize(4 * (last - first));
        this->op = op;
        this->f = f;
        this->size = last - first;
        this->build_from(0, first, last);
    }

    void __update(int left, int right, int node, const int update_pos, const T value)
    {
        if (update_pos < left or right <= update_pos)
        {
            return;
        }
        else if (left + 1 == right && left == update_pos)
        {
            st[node] = value;
        }
        else
        {
            int mid = left + (right - left) / 2;
            if (left <= update_pos && update_pos < mid)
            {
                __update(left, mid, 2 * node + 1, update_pos, value);
            }
            else if (mid <= update_pos && update_pos < right)
            {
                __update(mid, right, 2 * node + 2, update_pos, value);
            }
            st[node] = this->op(st[2 * node + 1], st[2 * node + 2]);
        }
    }

    void update(int pos, T value)
    {
        // assert(0 <= pos && pos < (int)this->st.size());
        __update(0, this->size, 0, pos, value);
    }

    T __range_query(int curr_l, int curr_r, int node, const int l, const int r)
    {
        // Loop invariant: [l, r) is always subrange of [curr_l, curr_r)
        // case 1: equal
        if (curr_l == l && curr_r == r)
        {
            return this->st[node];
        }
        else
        {
            int mid = curr_l + (curr_r - curr_l) / 2;
            // case 2: entirely inside left
            if (r <= mid)
            {
                return __range_query(curr_l, mid, 2 * node + 1, l, r);
            }
            // case 3: entirely inside right
            else if (l >= mid)
            {
                return __range_query(mid, curr_r, 2 * node + 2, l, r);
            }
            // case 4: intersects both children
            else
            {
                return this->op(__range_query(curr_l, mid, 2 * node + 1, l, mid),
                                __range_query(mid, curr_r, 2 * node + 2, mid, r));
            }
        }
    }

    T range_query(const int l, const int r)
    {
        return __range_query(0, this->size, 0, l, r);
    }
};

/**
 * @brief The range query operation in this segment tree returns the smallest index i
 * such that a[i] >= x
 * 
 * @tparam T: type with >= operator 
 */
template <typename T>
class LowerBoundSegmentTree: public SegmentTree<T>
{
    private:
        const int INF = 2e9;

    public:

        template <typename RandomAccessIterator>
        LowerBoundSegmentTree(RandomAccessIterator first,
                              RandomAccessIterator last,
                              T (*f)(T) = nullptr)
        : SegmentTree<T>(
                        first, 
                        last, 
                        [](T a, T b){if (a >= b) return a; else return b;}, 
                        f)
        {
            // calls base class constructor with op == max for type T
        }

        int __lower_bound_query(T x, int l, int r, int node)
        {
            if (l + 1 == r)
            {
                if (this->st[node] >= x)
                {
                    return l;
                } else 
                {
                    return INF; 
                }
            } else 
            {
                int mid = l + (r - l)/2;
                // case 1: there is a lower bound on left half
                if (SegmentTree<T>::range_query(l, mid) >= x)
                {
                    return __lower_bound_query(x, l, mid, 2*node + 1);
                } 
                // case 2: no lower bound on left half, but there is lower bound on right half
                else if (SegmentTree<T>::range_query(mid, r) >= x)
                {
                    return __lower_bound_query(x, mid, r, 2*node + 2);
                } 
                // case 3: did not found lower bound (max(i=1...n) a[i] < x)
                else {
                    return INF;
                }
            }
        }

        int lower_bound_query(T x)
        {
            return __lower_bound_query(x, 0, this->size, 0);
        }
};

/**
 * @brief The range query operation in this segment tree returns the smallest index i
 * such that a[i] <= x
 *
 * @tparam T: type with >= operator
 */
template <typename T>
class UpperBoundSegmentTree : public SegmentTree<T>
{
    private:
        const int INF = 2e9;

    public:
        template <typename RandomAccessIterator>
        UpperBoundSegmentTree(RandomAccessIterator first,
                              RandomAccessIterator last,
                              T (*f)(T) = nullptr)
            : SegmentTree<T>(
                  first,
                  last,
                  [](T a, T b)
                  {if (a <= b) return a; else return b; },
                  f)
        {
            // calls base class constructor with op == min for type T
        }

        int __upper_bound_query(T x, int l, int r, int node)
        {
            if (l + 1 == r)
            {
                if (this->st[node] >= x)
                {
                    return l;
                }
                else
                {
                    return INF;
                }
            }
            else
            {
                int mid = l + (r - l) / 2;
                // case 1: there is a upper bound on left half
                if (SegmentTree<T>::range_query(l, mid) <= x)
                {
                    return __upper_bound_query(x, l, mid, 2 * node + 1);
                }
                // case 2: no upper bound on left half, but there is upper bound on right half
                else if (SegmentTree<T>::range_query(mid, r) <= x)
                {
                    return __upper_bound_query(x, mid, r, 2 * node + 2);
                }
                // case 3: did not found upper bound (min(i=1...n) a[i] > x)
                else
                {
                    return INF;
                }
            }
        }

        int upper_bound_query(T x)
        {
            return __upper_bound_query(x, 0, this->size, 0);
        }
};

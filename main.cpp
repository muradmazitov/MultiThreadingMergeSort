#include <thread>
#include <iostream>
#include <vector>

void mergesort(std::vector <int> &a, int l, int r, int deep = 0)
{
    if (r - l <= 1)
        return;

    int mid = (l + r) / 2;

    if (deep <= 8)
    {
        std::thread left(mergesort, std::ref(a), l, mid, deep + 1);
        std::thread right(mergesort, std::ref(a), mid, r, deep + 1);
        left.join();
        right.join();
    }
    else
    {
        mergesort(a, l, mid, deep + 1);
        mergesort(a, mid, r, deep + 1);
    }

    std::unique_ptr<int[]>res(new int[r - l]);
    int lx = l, rx = mid, ix = 0;
    while (lx < mid && rx < r)
    {
        if (a[lx] < a[rx])
        {
            res[ix++] = a[lx++];
        }
        else
        {
            res[ix++] = a[rx++];
        }
    }

    if (lx != mid)
    {
        std::copy(&a[lx], &a[mid], &res[ix]);
    }
    else
    {
        std::copy(&a[rx], &a[r], &res[ix]);
    }

    std::copy(res.get(), res.get() + r - l, &a[l]);
}

int main()
{

    int n;
    std::cin >> n;
    std::vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }

    mergesort(v, 0, n);

    for (int i = 0; i < n; i++)
        std::cout << v[i] << ' ';
    return 0;
}

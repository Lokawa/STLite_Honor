#include <iostream>
#include <cstdio>

const int N = 1e6 + 5;
int row[N << 2], line[N << 2], n, m, q;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void row_pushup(int rt)
{
    row[rt] = row[rt << 1] + row[rt << 1 | 1];
}
void line_pushup(int rt)
{
    line[rt] = line[rt << 1] + line[rt << 1 | 1];
}
void row_update(int rt, int l, int r, int x, int op)
{
    if (l == r)
    {
        row[rt] = op;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        row_update(rt << 1, l, mid, x, op);
    else
        row_update(rt << 1 | 1, mid + 1, r, x, op);
    row_pushup(rt);
}
void line_update(int rt, int l, int r, int x, int op)
{
    if (l == r)
    {
        line[rt] = op;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        line_update(rt << 1, l, mid, x, op);
    else
        line_update(rt << 1 | 1, mid + 1, r, x, op);
    line_pushup(rt);
}
int row_find(int rt, int l, int r, int x)
{
    if (l == r)
    {
        if (row[rt]==0) return 1; else return 0;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        return row_find(rt << 1, l, mid, x);
    else
        return row_find(rt << 1 | 1, mid + 1, r, x);
}
int line_find(int rt, int l, int r, int x)
{
    if (l == r)
    {
        if (line[rt]==0) return 1; else return 0;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        return line_find(rt << 1, l, mid, x);
    else
        return line_find(rt << 1 | 1, mid + 1, r, x);
}
int row_query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return row[rt];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return row_query(rt << 1, l, mid, x, y);
    if (x > mid)
        return row_query(rt << 1 | 1, mid + 1, r, x, y);
    return row_query(rt << 1, l, mid, x, y) + row_query(rt << 1 | 1, mid + 1, r, x, y);
}
int line_query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return line[rt];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return line_query(rt << 1, l, mid, x, y);
    if (x > mid)
        return line_query(rt << 1 | 1, mid + 1, r, x, y);
    return line_query(rt << 1, l, mid, x, y) + line_query(rt << 1 | 1, mid + 1, r, x, y);
}
int main()
{
    n = read();
    m = read();
    q = read();
    for (int i = 0; i < q; i++)
    {
        int sign;
        sign = read();
        if (sign == 1)
        {
            int x, y;
            x = read();
            y = read();
            row_update(1, 1, n, x, row_find(1, 1, n, x));
            line_update(1, 1, m, y, line_find(1, 1, m, y));
        }
        else
        {
            int x1, y1, x2, y2;
            x1 = read();
            y1 = read();
            x2 = read();
            y2 = read();
            int r = row_query(1, 1, n, x1, x2), l = line_query(1, 1, m, y1, y2);
            int ans = r * (x2 - x1 + 1) + l * (y2 - y1 + 1) - r * l * 2;
            printf("%d\n", ans);
        }
    }
    system("pause");
    return 0;
}
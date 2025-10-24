#include <cstdio>
#include <algorithm>

constexpr int N = 205;
using namespace std;

// st: 时间戳, 用于标记每轮匹配
// a[i][j]: 邻接表，a[i][0] 存储 i 的邻居个数，a[i][1..a[i][0]] 存储邻居节点
// b[i]: 右侧节点 i 匹配的左侧节点（0表示未匹配）
// bz[i]: 节点 i 的访问时间戳, 用于避免重复访问
int st, a[N][N], b[N], bz[N];

bool match(int v)
{
    // 如果这个节点在本轮已经访问过，直接返回false（避免死循环）
    if(bz[v] == st) return 0;
    bz[v] = st; // 标记为已访问

    // 遍历v的所有邻居
    for(int i = 1; i <= a[v][0]; i++)
    {
        int u = a[v][i]; // u是v的邻居
        if(!b[u] || match(b[u]))
        {
            b[u] = v; // 将u匹配给v
            return 1; // 找到增广路径
        }
    }
    return 0; // 没有找到增广路径
}
int main()
{
    int n, k, x, y, ans = 0;
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= k; i++)
    {
        scanf("%d %d", &x, &y);
        y += n;
        a[x][++a[x][0]] = y;
        a[y][++a[y][0]] = x;
    }
    for(st = 1; st <= n; st++)
        if(match(st)) ans++;
    printf("%d", ans);
}
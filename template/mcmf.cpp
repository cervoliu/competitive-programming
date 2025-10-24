#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

// 最小费用最大流模板
constexpr int N = 5e3 + 5, M = 1e5 + 5;  // N: 最大节点数, M: 最大边数
constexpr int INF = 0x3f3f3f3f;          // 无穷大

// 全局变量定义
int n, m;           // n: 节点数, m: 边数
int tot = 1;        // 边的编号，从2开始（方便取反向边）
int lnk[N];         // 邻接表头节点
int cur[N];         // 当前弧优化，记录每个节点当前搜索到的边
int ter[M];         // 边的终点
int nxt[M];         // 邻接表中的下一条边
int cap[M];         // 边的容量
int cost[M];        // 边的费用
int dis[N];         // SPFA中的最短路距离
int ret;            // 总费用
bool vis[N];        // 访问标记数组

// 添加单向边 u -> v，容量为 w，费用为 c
void add(int u, int v, int w, int c) {
  ter[++tot] = v;      // 边的终点
  nxt[tot] = lnk[u];   // 链接到邻接表
  lnk[u] = tot;        // 更新头节点
  cap[tot] = w;        // 设置容量
  cost[tot] = c;       // 设置费用
}

// 添加双向边：正向边 u -> v (容量w, 费用c) 和反向边 v -> u (容量0, 费用-c)
void addedge(int u, int v, int w, int c) { 
  add(u, v, w, c);     // 正向边
  add(v, u, 0, -c);    // 反向边，容量为0，费用为负
}

// 使用 SPFA 算法寻找从 s 到 t 的最短路径（费用最小路径）
bool spfa(int s, int t) {
  memset(dis, 0x3f, sizeof(dis));    // 初始化距离为无穷大
  std::queue<int> q;
  q.push(s);           // 源点入队
  dis[s] = 0;          // 源点距离为0
  vis[s] = true;       // 标记源点已访问
  
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;    // 出队时取消访问标记
    
    // 遍历从节点 u 出发的所有边
    for (int i = lnk[u]; i; i = nxt[i]) {
      int v = ter[i];  // 边的终点
      // 如果边有剩余容量且可以松弛距离
      if (cap[i] && dis[v] > dis[u] + cost[i]) {
        dis[v] = dis[u] + cost[i];  // 更新最短距离
        if (!vis[v]) {              // 如果节点v不在队列中
          q.push(v);                // 将v加入队列
          vis[v] = true;            // 标记v已访问
        }
      }
    }
  }
  return dis[t] != INF;  // 返回是否能到达终点t
}

// 使用 DFS 寻找增广路径并计算最大流量
int dfs(int u, int t, int flow) {
  if (u == t) return flow;  // 到达终点，返回当前流量
  
  vis[u] = true;            // 标记当前节点已访问
  int ans = 0;              // 从当前节点能增广的总流量
  
  // 遍历从节点u出发的所有边（使用当前弧优化）
  for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
    int v = ter[i];         // 边的终点
    
    // 检查边是否可以增广：未访问、有剩余容量、在最短路径上
    if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
      // 递归搜索，流量为当前剩余容量和剩余需求的最小值
      int x = dfs(v, t, std::min(cap[i], flow - ans));
      
      if (x) {              // 如果找到了增广路径
        ret += x * cost[i]; // 累加费用
        cap[i] -= x;        // 减少正向边容量
        cap[i ^ 1] += x;    // 增加反向边容量
        ans += x;           // 累加增广流量
      }
    }
  }
  
  vis[u] = false;           // 回溯时取消访问标记
  return ans;               // 返回从当前节点增广的总流量
}

// 最小费用最大流主算法
int mcmf(int s, int t) {
  int ans = 0;              // 最大流量
  
  // 当存在从s到t的增广路径时继续
  while (spfa(s, t)) {
    memcpy(cur, lnk, sizeof(lnk));  // 重置当前弧
    int x;
    // 在当前费用最小的路径上尽可能多地增广
    while ((x = dfs(s, t, INF))) {
      ans += x;             // 累加流量
    }
  }
  
  return ans;               // 返回最大流量
}

int main() {
  int s, t;
  // 读入节点数n、边数m、源点s、汇点t
  scanf("%d%d%d%d", &n, &m, &s, &t);
  
  // 读入m条边的信息
  while (m--) {
    int u, v, w, c;
    scanf("%d%d%d%d", &u, &v, &w, &c);  // 起点u、终点v、容量w、费用c
    addedge(u, v, w, c);                 // 添加边到图中
  }
  
  // 计算最小费用最大流
  int ans = mcmf(s, t);                  // ans为最大流量
  printf("%d %d\n", ans, ret);           // 输出最大流量和最小费用
  
  return 0;
}
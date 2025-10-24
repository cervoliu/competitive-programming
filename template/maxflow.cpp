#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e4 + 5, M = 1e5 + 5;
const ll INF = 1e18;
int n, m, s, t;

int tot = 1, to[M], nxt[M], lst[N];
ll cap[M];

int level[N], cur[N];

void link(int u,int v,ll w) {
  to[++tot] = v;
  nxt[tot] = lst[u];
  lst[u] = tot;
  cap[tot] = w;
}

bool bfs() {
  memset(level, 0, sizeof(level));
  queue<int> q;
  q.push(s);
  level[s] = 1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = lst[u]; i; i = nxt[i]) {
      int v = to[i];
      if (cap[i] && !level[v]) {
        level[v] = level[u] + 1;
        q.push(v);
      }
    }
  }
  return level[t] > 0;
}

ll dfs(int u, ll flow) {
  if (u == t) return flow;
  ll ans = 0;
  for (int &i = cur[u]; i; i = nxt[i]) {
    int v = to[i];
    if (cap[i] && level[v] == level[u] + 1) {
      ll f = dfs(v, min(flow - ans, cap[i]));
      if (f > 0) {
        ans += f;
        cap[i] -= f;
        cap[i ^ 1] += f;
      }
    }
  }
  return ans;
}

ll dinic(int s, int t) {
  ll res = 0;
  while(bfs()) {
    memcpy(cur, lst ,sizeof(lst));
    ll x = 0;
    while((x = dfs(s, INF))) {
      res += x;
    }
  }
  return res;
}

int main() {
  freopen("input.txt", "r", stdin);
  scanf("%d%d%d%d", &n, &m, &s, &t);
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    link(u, v, w);
    link(v, u, 0);
  }

  ll ans = 0;

  ans = dinic(s, t);

  printf("%lld\n", ans);
  return 0;
}
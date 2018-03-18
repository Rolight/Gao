#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const long long hash_seed = 1313131;

vector<string> dict;
const int maxn = 1e6 + 10;
long long N, A, B, C, D, L;
char S1, S2;
char str[maxn];
long long x[maxn];
int cnt[maxn][26];
int tcnt[26];
bool vis[maxn];
typedef map<long long, int> CntHash;
typedef vector<vector<CntHash> > ChHash;
typedef map<int, ChHash> DictHash;
DictHash mp;
long long hv[26];

void inithv() {
  hv[0] = 1;
  for (int i = 1; i < 26; i++) {
    hv[i] = hv[i - 1] * hash_seed;
  }
}

long long getHash(int cnt[26]) {
  long long ret = 0;
  for (int i = 25; i >= 0; i--) {
    ret = ret * hash_seed + cnt[i];
  }
  return ret;
}

void initDict() {
  mp.clear();
  for (int i = 0; i < L; i++) {
    string &now = dict[i];
    int nowlen = now.length();
    int head_ch = now[0] - 'a', back_ch = now[nowlen - 1] - 'a';
    memset(tcnt, 0, sizeof(tcnt));
    for (int j = 0; j < nowlen; j++) {
      tcnt[now[j] - 'a']++;
    }
    if (mp.count(nowlen) == 0) {
      for (int i = 0; i < 26; i++) {
        vector<CntHash> vec;
        mp[nowlen].push_back(vec);
        for (int j = 0; j < 26; j++) {
          CntHash c;
          mp[nowlen][i].push_back(c);
        }
      }
    }
    mp[nowlen][head_ch][back_ch][getHash(tcnt)]++;
  }
}

int gao() {
  int ans = 0;
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < N; i++) {
    int pos = i + 1;
    cnt[i][str[i] - 'a']++;
    if (i == 0)
      continue;
    for (int j = 0; j < 26; j++) {
      cnt[i][j] += cnt[i - 1][j];
    }
  }
  initDict();
  int iterc = 0;
  long long curHash = 0;
  for (DictHash::iterator iter = mp.begin(); iter != mp.end(); ++iter) {
    int cur_length = iter->first;
    for (int i = 0; i + cur_length - 1 < N; i++) {
      int cur_head = str[i] - 'a', cur_tail = str[i + cur_length - 1] - 'a';
      if (i == 0) {
        memset(tcnt, 0, sizeof(tcnt));
        for (int j = 0; j < cur_length; j++) {
          tcnt[str[j] - 'a']++;
        }
        curHash = getHash(tcnt);
      } else {
        curHash -= hv[str[i - 1] - 'a'];
        curHash += hv[str[i + cur_length - 1] - 'a'];
        tcnt[str[i - 1] - 'a']--;
        tcnt[str[i + cur_length - 1] - 'a']++;
      }
      long long cur_hash = curHash;
      if (iter->second[cur_head][cur_tail].count(cur_hash) != 0) {
        ans += iter->second[cur_head][cur_tail][cur_hash];
        iter->second[cur_head][cur_tail].erase(cur_hash);
      }
    }
  }
  return ans;
}

int main() {
  inithv();
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    cin >> L;
    string buf;
    dict.clear();
    int lsum = 0;
    for (int i = 1; i <= L; i++) {
      cin >> buf;
      dict.push_back(buf);
      lsum += buf.length();
    }
    cin >> S1 >> S2 >> N >> A >> B >> C >> D;
    str[0] = S1;
    str[1] = S2;
    x[0] = S1;
    x[1] = S2;
    for (int i = 2; i < N; i++) {
      x[i] = (A * (int)x[i - 1] + B * (int)x[i - 2] + C) % D;
      str[i] = x[i] % 26 + 97;
    }
    str[N] = 0;
    int ans = gao();
    printf("Case #%d: %d\n", kase, ans);
  }
  return 0;
}

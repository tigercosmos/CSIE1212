#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
typedef long long LL;
#define Min(A, B) std::min(A, B)
const LL MaxN = 100;
#define Inf 0x3f3f3f3f
LL T, N, M;
struct Node {
  double X, Y;
} P[MaxN];
#define Abs(A) fabs(A)
LL F[(1 << 25) - 1], G[MaxN][MaxN];
void Init() {
  for (LL i = 0; i <= N; i++)
    for (LL j = 0; j <= N; j++)
      G[i][j] = 0;
  LL S = (1 << N) - 1;
  for (LL i = 0; i < (1 << 25) - 1; i++)
    F[i] = Inf;
}

void First() {
  double A, B;
  for (LL i = 1; i <= N; i++)
    for (LL j = i + 1; j <= N; j++) {
      double C = P[i].X, D = P[j].X;
      double E = C - D;
      if (fabs(E) <= 1e-7)
        continue;
      A = ((P[i].Y / P[i].X) - (P[j].Y / P[j].X)) / (P[i].X - P[j].X);
      if (A >= 0.0)
        continue;
      B = (P[i].Y / P[i].X) - (A * P[i].X);
      for (LL k = 1; k <= N; k++) {
        C = P[k].X * A + B, D = P[k].Y / P[k].X;
        E = C - D;
        if (fabs(E) <= 1e-7)
          G[i][j] |= (1 << (k - 1));
      }
    }
}

int main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld", &N);
    Init();
    for (LL i = 1; i <= N; i++) {
      double A, B;
      scanf("%lf%lf", &A, &B);
      P[i] = (Node){A, B};
    }
    First();
    LL S = (1 << N) - 1;
    F[0] = 0;
    F[S] = Inf;
    for (LL i = 0; i <= S; i++)
      for (LL j = 1; j <= N; j++)
        if (!(i & (1 << (j - 1)))) {
          for (LL k = j; k <= N; k++) {
            if (k == j) {
              LL Now = i | (1 << (j - 1));
              F[Now] = Min(F[Now], F[i] + 1);
              continue;
            }
            double C = P[k].X, D = P[j].X;
            double E = C - D;
            LL NowW = i | G[j][k];
            if (fabs(E) <= 1e-7)
              continue;
            F[NowW] = Min(F[NowW], F[i] + 1);
          }
          break;
        }
    printf("%lld\n", F[(1 << N) - 1]);
  }
}
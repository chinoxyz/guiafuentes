lint digitsum(lint r, lint m) {
  // sum from 0 to r - digits base m
  lint ret = 0;
  for (lint x = 1; x <= r; x *= m) {
    lint dig = (r / x) % m;
    lint le = (r / x) / m;
    lint ri = r % x;
    lint cur = 0;
    for (int i = 1; i < dig; ++i) cur += i;
    ret += cur * (le + 1) * x;
    ret += dig * (le * x + ri + 1);
    cur = 0;
    for (int i = dig + 1; i < m; ++i) cur += i;
    ret += cur * le * x;
  }
  return ret;
}

**NOTE:** we suppose without loss of generality that all elements of $a$ are distinct  
and that $a$ is sorted non-decreasing  
(if not, just remove duplicates and sort it)

---

### Lemma 1
The answer is 1 step **iff**  
$$
\gcd(\{a[i+1] - a[i] : 0 \le i < n-1\}) > 1.
$$

**Proof:**  
Let $d$ be this gcd.  

- ($\Rightarrow$) If the answer is 1, there exists $m > 1$ and some $x$ such that  
$$
a[i] \equiv x \pmod m \quad \text{for all } i,
$$
so $a[i+1] - a[i]$ is divisible by $m$ for all $i$.

- ($\Leftarrow$) If $d > 1$, then  
$$
a[n-1] \equiv a[n-2] \equiv \dots \equiv a[0] \pmod d.
$$

---

### Lemma 2
The answer is always at most 2.

**Proof:**  
Trivial (as $M = 2$ is a candidate to solve the problem in at most two steps).

---

We can now analyze remainders:

If $N \ge 3$, then the sequence starts out as one of the following:
- $x, x, \dots$
- $x, y, x, \dots$
- $x, y, y, \dots$

Therefore, $m$ is a divisor of either:
$$
a[1] - a[0], \quad a[2] - a[0], \quad \text{or} \quad a[2] - a[1].
$$

We can collect these divisors in  
$$
O\bigl(3 \cdot (\max_{i=1..M} \mathrm{div}(i) + \sqrt{M}\bigr))
= O\bigl(M^{1/3} + \sqrt{M}\bigr) = O\bigl(\sqrt{M}\bigr)
$$
where $\mathrm{div}(x)$ is the number of divisors of $x$
and then merge them into a set (to avoid double counting) in  
$$
O(M^{1/3}\log M).
$$  
Checking if a divisor is valid is $O(N)$.

Thus the final complexity is:  
$$
O\bigl(N\log N \;+\; \sqrt{M} + M^{1/3}\log M \;+\; N M^{1/3}\bigr).
$$

If $N = 2$, and there is no solution in 1 step,  
then any $1 < m \le M$ is a solution.

---

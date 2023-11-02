(define (filtered-accumulate combiner null-value term a next b pred?)
  (if (> a b)
    null-value
    (combiner
      (if (pred? a) (term a) null-value)
      (filtered-accumulate combiner null-value term (next a) next b pred?))))

; sum even numbers on the range
(define (sum-even a b)
  (define (term x) x)
  (define (next x) (+ x 1))
  (filtered-accumulate + 0 term a next b even?))

; prime? procedure using the fermat test
(define (prime? n)
  (define (fast-prime? n times)
    (define (fermat-test n)
      (try-it (+ 1 (random (- n 1)))))

    (define (try-it a)
      (= (expmod a n n) a))

    (define (expmod base exp m)
      (cond ((= exp 0) 1)
            ((even? exp)
             (remainder (square (expmod base (/ exp 2) m)) m))
            (else
              (remainder (* base (expmod base (- exp 1) m)) m))))

    (cond ((= times 0) #t)
          ((fermat-test n) (fast-prime? n (- times 1)))
          (else #f)))
  (fast-prime? n 100))

(define (square x) (* x x))

(define (gcd a b)
  (if (= b 0)
    a
    (gcd b (remainder a b))))

; sum squares of primes on the range
(define (prime-sum a b)
  (define (term x) (square x))
  (define (next x) (+ x 1))
  (filtered-accumulate + 0 term a next b prime?))

; product of relative primes
(define (prime-prod n)
  (define (term x) x)
  (define (next x) (+ x 1))
  (define (rel-prime? x)
    (= (gcd x n) 1))
  (filtered-accumulate * 1 term 1 next (- n 1) rel-prime?))

; testing procedures
(display (sum-even 1 10)) (newline) ; 30
(display (prime-sum 2 10)) (newline) ; 87
(display (prime-prod 10)) (newline) ; 189

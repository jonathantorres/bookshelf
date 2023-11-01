(use-modules (srfi srfi-19))

(define (timed-mr-test n)
  (newline)
  (display n)
  (start-mr-test n (runtime)))

(define (start-mr-test n start-time)
  (if (fast-prime? n 100)
    (report-prime (- (runtime) start-time))))

(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))

(define (fast-prime? n times)
  (cond ((= times 0) #t)
        ((mr-test n) (fast-prime? n (- times 1)))
        (else #f)))

(define (mr-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
           (squaremod (expmod base (/ exp 2) m) m))
        (else
          (remainder (* base (expmod base (- exp 1) m)) m))))

(define (squaremod a m)
  (define r (remainder (square a) m))
  (if (and (not (= a 1)) (not (= a (- m 1))) (= r 1))
    0
    r))

(define (square x)
  (* x x))

(define (runtime)
  (/ (time-nanosecond (current-time time-utc)) 1000))

; testing a few non-primes
(timed-mr-test 500)
(timed-mr-test 50343)

; testing a few primes
(timed-mr-test 100003)
(timed-mr-test 100019)
(timed-mr-test 100043)

; testing charmichael numbers
(timed-mr-test 561)
(timed-mr-test 1105)
(timed-mr-test 1729)
(timed-mr-test 2465)
(timed-mr-test 2821)
(timed-mr-test 6601)
(newline)

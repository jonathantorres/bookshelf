; using fast-exp appears to be too slow
; since it computes values for exponents that are too big

(use-modules (srfi srfi-19))

(define (timed-prime-test n)
  (newline)
  (display n)
  (start-prime-test n (runtime)))

(define (start-prime-test n start-time)
  (if (fast-prime? n 1)
    (report-prime (- (runtime) start-time))))

(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))

(define (fast-prime? n times)
  (cond ((= times 0) #t)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else #f)))

(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (expmod base exp m)
  (remainder (fast-exp base exp) m))

(define (runtime)
  (/ (time-nanosecond (current-time time-utc)) 1000))

(define (fast-exp b n)
  (exp-iter 1 b n))

(define (fast-exp b n)
  (define (exp-iter a b n)
    (cond ((= n 0) a)
          ((even? n)
           (exp-iter a (square b) (/ n 2)))
          (else (exp-iter (* a b) b (- n 1)))))
  (exp-iter 1 b n))

(define (even? n)
  (= (remainder n 2) 0))

(define (square x)
  (* x x))

(timed-prime-test 1009)
(timed-prime-test 1013)
(timed-prime-test 1019)

(timed-prime-test 10007)
(timed-prime-test 10009)
(timed-prime-test 10037)

(timed-prime-test 100003)
(timed-prime-test 100019)
(timed-prime-test 100043)

(timed-prime-test 1000003)
(timed-prime-test 1000033)
(timed-prime-test 1000037)
(newline)

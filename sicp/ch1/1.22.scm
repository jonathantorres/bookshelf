(use-modules (srfi srfi-19))

(define (timed-prime-test n)
  (newline)
  (display n)
  (start-prime-test n (runtime)))

(define (start-prime-test n start-time)
  (if (prime? n)
    (report-prime (- (runtime) start-time))))

(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))

(define (prime? n)
  (= n (smallest-divisor n)))

(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (runtime)
  (/ (time-nanosecond (current-time time-utc)) 1000))

(define (square x)
  (* x x))

(define (search-for-primes start end)
  (cond ((>= start end) "")
        ((even? start) (search-for-primes (+ start 1) end))
        (else (timed-prime-test start) (search-for-primes (+ start 2) end))))

; search for primes from 1,001 to 9,999
; primes found: 1,009, 1,013 and 1,019
(search-for-primes 1001 9999)

; search for primes from 10,001 to 99,999
; primes found: 10,007, 10,009 and 10,037
(search-for-primes 10001 99999)

; search for primes from 100,000 to 999,999
; primes found: 100,003, 100,019 and 100,043
(search-for-primes 100000 999999)

; search for primes from 1,000,001 to 10,000,000
; primes found: 1,000,003, 1,000,033 and 1,000,037
(search-for-primes 1000000 10000000)

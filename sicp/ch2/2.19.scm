; No, the order does not affect the answer produced by cc, since it checks for all possibilities
(define (cc amount coin-values)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (no-more? coin-values)) 0)
        (else
          (+ (cc amount (except-first-denomination coin-values))
             (cc (- amount (first-denomination coin-values)) coin-values)))))

(define (first-denomination coin-values)
  (car coin-values))

(define (except-first-denomination coin-values)
  (cdr coin-values))

(define (no-more? coin-values)
  (define (length l)
    (if (null? l)
      0
      (+ 1 (length (cdr l)))))
  (= (length coin-values) 0))

(define us-coins (list 50 25 10 5 1))

(display (cc 100 us-coins)) (newline)

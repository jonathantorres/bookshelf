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

(display (fast-exp 2 2)) (newline)
(display (fast-exp 2 32)) (newline)
(display (fast-exp 3 4)) (newline)
(display (fast-exp 5 5)) (newline)

; recursive version of accumulate
(define (accumulate combiner null-value term a next b)
  (if (> a b)
    null-value
    (combiner (term a) (accumulate combiner null-value term (next a) next b))))

; iterative version of accumulate
(define (accumulate-iter combiner null-value term a next b)
  (define (iter a r)
    (if (> a b)
      r
      (iter (next a) (combiner r (term a)))))
  (iter a null-value))

; sum procedure using accumulate
(define (sum term a next b)
  (accumulate + 0 term a next b))

; product procedure using accumulate
(define (product term a next b)
  (accumulate * 1 term a next b))

; sum-integers function using sum
(define (sum-integers a b)
  (define (term x) x)
  (define (inc x) (+ x 1))
  (sum term a inc b))

; factorial function using product
(define (factorial n)
  (define (term x) x)
  (define (next x) (+ x 1))
  (product term 1 next n))

(display (sum-integers 1 10)) (newline) ;; 55
(display (factorial 5)) (newline) ;; 120


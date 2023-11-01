(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter (next a) (+ result (term a)))))
  (iter a 0))

(define (sum-integers a b)
  (define (term x) x)
  (define (inc x) (+ x 1))
  (sum term a inc b))

(define (sum-cubes a b)
  (define (term x) (* x x x))
  (define (inc x) (+ x 1))
  (sum term a inc b))

(display (sum-integers 1 10)) (newline) ;; 55
(display (sum-cubes 1 10)) (newline) ;; 3025

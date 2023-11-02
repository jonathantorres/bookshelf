; recursive version of product
(define (product term a next b)
  (if (> a b)
    1
    (* (term a) (product term (next a) next b))))

; iterative version of product
(define (product-iter term a next b)
  (define (iter a r)
    (if (> a b)
      r
      (iter (next a) (* r (term a)))))
  (iter a 1))

; factorial function using product
(define (factorial n)
  (define (term x) x)
  (define (next x) (+ x 1))
  (product term 1 next n))

; approximation to pi function
(define (pi-approx n)
  (define (next x) (+ x 1.0))
  (define (term x)
    (if (even? x)
      (/ (+ x 2.0) (+ x 1.0))
      (/ (+ x 1.0) (+ x 2.0))))
  (* 4.0 (product term 1.0 next n)))

(display (factorial 5)) (newline) ;; 120
(display (pi-approx 1000)) (newline)


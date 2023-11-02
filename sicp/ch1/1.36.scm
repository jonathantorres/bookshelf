(define (fixed-point f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (display guess)
    (newline)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(define (f y)
  (fixed-point (lambda (x) (/ (log y) (log x))) 2.0))

(define (g y)
  (fixed-point (lambda (x) (average x (/ (log y) (log x)))) 2.0))

(define (average x y)
  (/ (+ x y) 2))

(display (f 1000)) (newline)
(display "----------------") (newline)
(display (g 1000)) (newline)

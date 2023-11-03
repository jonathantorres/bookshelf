(define (repeated f n)
  (if (= n 1)
    f
    (compose f (repeated f (- n 1)))))

(define (fixed-point f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (average x y)
  (/ (+ x y) 2))

(define (square x) (* x x))

(define (cube x) (* x x x))

(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y))) 1.0))

(define (cube-root x)
  (fixed-point (average-damp (lambda (y) (/ x (square y)))) 1.0))

(define (fourth-root x)
  (fixed-point ((repeated average-damp 2) (lambda (y) (/ x (cube y)))) 1.0))

(define (nth-root n x)
  (define (calc-repeats n)
    (floor (/ (log n) (log 2))))
  (let ((repeats (calc-repeats n)))
    (fixed-point
      ((repeated average-damp repeats) (lambda (y) (/ x (expt y (- n 1)))))
      1.0)))

(display (sqrt 25)) (newline)
(display (nth-root 2 25)) (newline)

(display (cube-root 27)) (newline)
(display (nth-root 3 27)) (newline)

(display (fourth-root 49)) (newline)
(display (nth-root 4 49)) (newline)


(define (iterative-improve good-enough? improve)
  (lambda (guess)
    (if (good-enough? guess)
      guess
       ((iterative-improve good-enough? improve) (improve guess)))))

(define (sqrt x)
  (define tolerance 0.001)
  (define (good-enough? guess)
    (< (abs (- (square guess) x)) tolerance))
  (define (improve guess)
    (average guess (/ x guess)))
  ((iterative-improve good-enough? improve) 1.0))

(define (fixed-point f first-guess)
  (define tolerance 0.00001)
  (define (good-enough? guess)
    (< (abs (- guess (f guess))) tolerance))
  ((iterative-improve good-enough? f) first-guess))


(define (square x) (* x x))
(define (average x y) (/ (+ x y) 2))


(display (sqrt 25)) (newline)
(display (fixed-point cos 1.0)) (newline)
(display (fixed-point (lambda (y) (+ (sin y) (cos y))) 1.0)) (newline)

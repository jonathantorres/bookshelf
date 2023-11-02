(define (newtons-method g guess)
  (define (newton-transform g)
    (lambda (x)
      (- x (/ (g x) ((deriv g) x)))))

  (define (deriv g)
    (define dx 0.00001)
    (lambda (x)
      (/ (- (g (+ x dx)) (g x)) dx)))
  (fixed-point (newton-transform g) guess))

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

; cubic definition to be used with newtons-method
(define (cubic a b c)
  (lambda (x) (+ (* x x x) (* a (* x x)) (* b x) c)))

(display (newtons-method (cubic 1 2 3) 1)) (newline)


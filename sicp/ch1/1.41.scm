(define (double f)
  (lambda (x) (f (f x))))

(define (inc x) (+ x 1))

; the value returned is 21
(display (((double (double double)) inc) 5)) (newline)

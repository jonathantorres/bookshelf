(define (make-rat n d)
  (define den (abs d))
  (let ((g (gcd n den)))
    (cons (/ n g) (/ den g))))

(define (numer x) (car x))

(define (denom x) (cdr x))

(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

(define a (make-rat 1 2))
(define b (make-rat -8 -7))
(define c (make-rat -4 2))
(define d (make-rat 10 -5))
(define e (make-rat 8 -12))

(print-rat a)
(print-rat b)
(print-rat c)
(print-rat d)
(print-rat e)
(newline)

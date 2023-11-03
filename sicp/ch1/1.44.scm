(define (nfold-smooth f n)
  (define (smooth f)
    (define dx 0.00001)
    (lambda (x)
      (average (f (- x dx)) (+ (f x) (f (+ x dx))))))
  ((repeated smooth n) f))

(define (repeated f n)
  (define (compose f g)
    (lambda (x) (f (g x))))
  (cond ((= n 0) (lambda (x) x))
        ((= n 1) (lambda (x) (f x)))
        (else (compose f (repeated f (- n 1))))))

(define (average x y)
  (/ (+ x y) 2))

(define (square x) (* x x))

(display ((nfold-smooth square 10) 2)) (newline)

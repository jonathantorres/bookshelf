(define (cont-frac n d k)
  (define (iter r k)
    (if (= k 0)
      r
      (iter (/ (n k) (+ (d k) r)) (- k 1))))
  (iter 0 k))

(define (tan-cf x k)
  (cont-frac
    (lambda (i) (if (= i 1) x (- (square x))))
    (lambda (i) (- (* i 2) 1))
    k))

(define (square x) (* x x))

(display (tan-cf 1.0 100)) (newline)
(display (tan-cf 2.0 100)) (newline)
(display (tan-cf 3.141592 100)) (newline)



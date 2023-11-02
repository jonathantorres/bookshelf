; k must be at least 6 in order to get an approximation that is accurate to 4 decimal places

; recursive continued fraction
(define (cont-frac n d k)
  (if (= k 1)
    (/ (n k) (d k))
    (/ (n k) (+ (d k) (cont-frac n d (- k 1))))))

; iterative continued fraction
(define (cont-frac-iter n d k)
  (define (iter n d r k)
    (if (= k 1)
      r
      (iter n d (/ (n k) (+ (d k) r)) (- k 1))))
  (iter n d 1 k))

(display (cont-frac
    (lambda (i) 1.0)
    (lambda (i) 1.0)
    10))
(newline)

(display (cont-frac-iter
    (lambda (i) 1.0)
    (lambda (i) 1.0)
    10))
(newline)

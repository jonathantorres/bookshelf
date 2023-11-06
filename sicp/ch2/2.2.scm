(define (make-segment x y)
  (cons x y))

(define (start-segment s)
  (car s))

(define (end-segment s)
  (cdr s))

(define (make-point x y)
  (cons x y))

(define (x-point p)
  (car p))

(define (y-point p)
  (cdr p))

(define (midpoint-segment s)
  (define (avg x y)
    (/ (+ x y) 2))
  (let ((start (start-segment s))
        (end (end-segment s)))
    (make-point
      (avg (x-point start) (x-point end))
      (avg (y-point start) (y-point end)))))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(define s (make-segment
            (make-point 2 2)
            (make-point 4 2)))

(define mid (midpoint-segment s))

(print-point (start-segment s))
(print-point (end-segment s))
(print-point mid)
(newline)

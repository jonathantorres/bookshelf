(define (make-segment v1 v2)
  (cons v1 v2))

(define (start-segment s)
  (car s))

(define (end-segment s)
  (cdr s))

(define seg (make-segment 1 2))
(display seg) (newline)
(display (start-segment seg)) (newline)
(display (end-segment seg)) (newline)

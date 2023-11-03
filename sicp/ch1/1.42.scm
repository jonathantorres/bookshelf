(define (compose f g)
  (lambda (x) (f (g x))))

(define (square x) (* x x))

(define (inc x) (+ x 1))

(display ((compose square inc) 6)) (newline) ; 49

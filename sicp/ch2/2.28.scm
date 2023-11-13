(define (fringe tree)
  (cond ((null? tree) tree)
        ((not (pair? (car tree)))
         (cons (car tree) (fringe (cdr tree))))
        (else
          (append (fringe (car tree)) (fringe (cdr tree))))))

(define x (list (list 1 2) (list 3 4)))
(define y (list x x))
(define z (list 1 (list 2) (list 3 4) 5 6 (list 7 8) 9 10))

(display (fringe x)) (newline)
(display (fringe y)) (newline)
(display (fringe z)) (newline)

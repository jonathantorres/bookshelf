; direct definition
(define (square-tree tree)
  (cond ((null? tree) tree)
        ((not (pair? tree)) (square tree))
        (else
          (cons (square-tree (car tree)) (square-tree (cdr tree))))))

; definition with map
(define (square-tree-map tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
           (square-tree-map sub-tree)
           (square sub-tree)))
         tree))

(define (square x) (* x x))

(define t (list 1
                (list 2 (list 3 4) 5)
                (list 6 7)))

(display (square-tree t)) (newline)
(display (square-tree-map t)) (newline)

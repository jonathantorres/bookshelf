; direct definition
(define (tree-map f tree)
  (cond ((null? tree) tree)
        ((not (pair? tree)) (f tree))
        (else
          (cons (tree-map f (car tree)) (tree-map f (cdr tree))))))

; definition with map
(define (tree-map-map f tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
           (tree-map-map f sub-tree)
           (f sub-tree)))
       tree))

(define (square-tree tree)
  (tree-map square tree))

(define (square-tree-map tree)
  (tree-map-map square tree))

(define (square x) (* x x))

(define t (list 1
                (list 2 (list 3 4) 5)
                (list 6 7)))

(display (square-tree t)) (newline)
(display (square-tree-map t)) (newline)

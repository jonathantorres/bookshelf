(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        (else (adjoin-set (car set1) (union-set (cdr set1) set2)))))

(define (element-of-set? x set)
  (cond ((null? set) #f)
        ((equal? x (car set)) #t)
        (else (element-of-set? x (cdr set)))))

(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (cons (car set1) (intersection-set (cdr set1) set2)))
        (else (intersection-set (cdr set1) set2))))

(define (adjoin-set x set)
    (cons x set))

(define x (list 1 2 3 4))
(define y (list 3 4 5 6))
(define z (list 3 3 4 5 6 7 8 9 1))

(display (element-of-set? 1 (list 1 2 3))) (newline) ; #t
(display (element-of-set? 5 (list 1 2 3))) (newline) ; #f
(display (adjoin-set 1 (list 1 2 3))) (newline)      ; (1 1 2 3)
(display (adjoin-set 4 (list 1 2 3))) (newline)      ; (4 1 2 3)
(display (union-set x y)) (newline)                  ; (1 2 3 4 3 4 5 6)
(display (intersection-set x z)) (newline)           ; (3 4)
